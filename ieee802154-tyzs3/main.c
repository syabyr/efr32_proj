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
#include "radio.h"
#include "timer.h"


volatile uint32_t msTicks; /* counts 1ms timeTicks */

int channel;

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

    // Toggle LED0

    channel --;
    if(channel < 11)
    {
        channel = 11;
    }
    printf("set channel to %d\r\n",channel);
    set_channel(channel);
}

/**************************************************************************//**
 * @brief GPIO Odd IRQ for pushbuttons on odd-numbered pins
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
    // Clear all odd pin interrupt flags
    GPIO_IntClear(0xAAAA);

    // Toggle LED01
    //printf("key2\r\n");
    channel ++;
    if(channel > 26)
    {
        channel = 26;
    }
    printf("set channel to %d\r\n",channel);
    set_channel(channel);
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
    GPIO_PinModeSet(gpioPortF, 4, gpioModeInputPullFilter, 1);
    GPIO_PinModeSet(gpioPortF, 5, gpioModeInputPullFilter, 1);

    // Enable IRQ for even numbered GPIO pins
    NVIC_EnableIRQ(GPIO_EVEN_IRQn);

    // Enable IRQ for odd numbered GPIO pins
    NVIC_EnableIRQ(GPIO_ODD_IRQn);

    // Enable falling-edge interrupts for PB pins
    GPIO_ExtIntConfig(gpioPortF, 4,4, 0, 1, true);
    GPIO_ExtIntConfig(gpioPortF, 5, 5, 0, 1, true);

    radio_init();

    channel = 15;
    set_channel(channel);


    zrepl_active = 1;
    static const char version[] = "hello ieee802.15.4" ;
    ieee802154_send(version, sizeof(version) - 1);
    zrepl_active = 0;


    printf("test\r\n");

    /* Infinite blink loop */
    while (1)
    {
        Delay(1000);
        toggleLed();
        //printf("helloworld\r\n");
    }
}



