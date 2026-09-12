//EFM32 blink test

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "retargetserial.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_usart.h"

#include "led.h"
#include "uart0.h"
#include "sniffer.h"
#include "timer.h"


volatile uint32_t msTicks; /* counts 1ms timeTicks */

/* Zigbee channels to cycle through (11..26) */
static const int channels[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
#define CHANNEL_COUNT (sizeof(channels) / sizeof(channels[0]))
static int channel_index = 4; /* start at channel 15 */

#define BUTTON_DEBOUNCE_MS 50
static volatile uint32_t last_button_ms;

/* set by the button IRQ to request a "switched channel" LED blink */
static volatile uint8_t switch_led_flag;

/* apply the current channel_index: switch radio, echo, blink */
static void channel_apply(void)
{
    set_channel(channels[channel_index]);
    printf("CH %d\r\n", channels[channel_index]);
    switch_led_flag = 1;
}

/* step the channel by delta (wraps around the table) */
static void channel_step(int delta)
{
    channel_index = (channel_index + delta + CHANNEL_COUNT) % CHANNEL_COUNT;
    channel_apply();
}

/* jump to an absolute channel (11..26), ignored if out of range */
static void channel_set_abs(int ch)
{
    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
        if (channels[i] == ch)
        {
            channel_index = i;
            channel_apply();
            return;
        }
    }
    printf("ERR\r\n");
}

/* serial command parser state: accumulated absolute channel number */
static int cmd_num = -1;

static void cmd_feed(int c)
{
    switch (c)
    {
        case '+': case 'n': case 'N':
            channel_step(+1);
            cmd_num = -1;
            break;
        case '-': case 'p': case 'P':
            channel_step(-1);
            cmd_num = -1;
            break;
        case '?':
            printf("CH %d\r\n", channels[channel_index]);
            cmd_num = -1;
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            if (cmd_num < 0)
                cmd_num = 0;
            cmd_num = cmd_num * 10 + (c - '0');
            break;
        case '\r': case '\n':
            if (cmd_num >= 0)
            {
                channel_set_abs(cmd_num);
                cmd_num = -1;
            }
            break;
        default:
            cmd_num = -1;
            break;
    }
}

/* non-blocking LED blink state machine, driven by msTicks */
#define LED_HALF_MS 30
static uint8_t  led_toggles_left;
static uint32_t led_next_ms;

static void led_service(void)
{
    if (led_toggles_left == 0)
    {
        if (switch_led_flag)
        {
            switch_led_flag = 0;
            led_toggles_left = 4;   /* 2 blinks */
        }
        else if (sniffer_rx_flag)
        {
            sniffer_rx_flag = 0;
            led_toggles_left = 2;   /* 1 blink */
        }
        else
        {
            return;
        }
        led_next_ms = msTicks;      /* toggle immediately */
    }

    if ((int32_t)(msTicks - led_next_ms) < 0)
        return;

    toggleLed();
    led_toggles_left--;
    led_next_ms = msTicks + LED_HALF_MS;
}

void Delay(uint32_t dlyTicks);

/**************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 *****************************************************************************/
void SysTick_Handler(void)
{
    msTicks++;       /* increment counter necessary in Delay()*/
}

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void Delay(uint32_t dlyTicks)
{
    uint32_t curTicks;

    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks) ;
}

/**************************************************************************//**
 * @brief GPIO Even IRQ for pushbuttons on even-numbered pins
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
    // Clear all even pin interrupt flags
    GPIO_IntClear(0x5555);

    // simple software debounce on top of the hardware glitch filter
    uint32_t now = msTicks;
    if (now - last_button_ms < BUTTON_DEBOUNCE_MS)
        return;
    last_button_ms = now;

    channel_step(+1);
}

/**************************************************************************//**
 * @brief GPIO Odd IRQ for pushbuttons on odd-numbered pins
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
}

/* blocking LED blink, called from the main loop only */
static void led_blink(int times, uint32_t on_ms, uint32_t off_ms)
{
    for (int i = 0; i < times; i++)
    {
        ledOn();
        Delay(on_ms);
        ledOff();
        Delay(off_ms);
    }
}


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
    CHIP_Init();

    EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
    EMU_DCDCInit(&dcdcInit);

    CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;
    CMU_HFXOInit(&hfxoInit);

    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

    CMU_ClockEnable(cmuClock_CORELE, true);

    CMU_ClockEnable(cmuClock_RTCC, true);

    CMU_ClockEnable(cmuClock_CRYPTO, true);

    CMU_ClockEnable(cmuClock_GPIO, true);

    CMU_ClockEnable(cmuClock_TIMER1, true );

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;


    initUart0();
    initLed();
    initTimer0();

    // Configure PB12 and PB13 as input with glitch filter enabled
    //GPIO_PinModeSet(gpioPortB, 12, gpioModeInputPullFilter, 1);
    //GPIO_PinModeSet(gpioPortB, 13, gpioModeInputPullFilter, 1);
    GPIO_PinModeSet(gpioPortA, 0, gpioModeInputPullFilter, 1);

    // Enable IRQ for even numbered GPIO pins
    NVIC_EnableIRQ(GPIO_EVEN_IRQn);

    // Enable IRQ for odd numbered GPIO pins
    //NVIC_EnableIRQ(GPIO_ODD_IRQn);

    // Enable falling-edge interrupts for PB pins
    //GPIO_ExtIntConfig(gpioPortB, 12,12, 0, 1, true);
    //GPIO_ExtIntConfig(gpioPortB, 13, 13, 0, 1, true);
    GPIO_ExtIntConfig(gpioPortA, 0, 0, 0, 1, true);

    radio_init();

    set_channel(channels[channel_index]);


    zrepl_active = 1;
    static const char version[] = "hello ieee802.15.4" ;
    ieee802154_send(version, sizeof(version) - 1);
    zrepl_active = 0;


    printf("test\r\n");

    /* Event-driven LED loop: blink on channel switch and on RX */
    while (1)
    {
        if (switch_led_flag)
        {
            switch_led_flag = 0;
            led_blink(2, 40, 40);
        }
        if (sniffer_rx_flag)
        {
            sniffer_rx_flag = 0;
            led_blink(1, 30, 30);
        }
        Delay(1);
    }
}



