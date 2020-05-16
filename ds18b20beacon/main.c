//EFM32 blink test

#ifndef LED_PIN
#define LED_PIN     13
#endif
#ifndef LED_PORT
#define LED_PORT    gpioPortB
#endif



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
#include "ds18b20.h"


volatile uint32_t msTicks; /* counts 1ms timeTicks */

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
    initTimer1();

    radio_init();

    zrepl_active = 1;
    static const char version[] = "hello ieee802.15.4" ;
    ieee802154_send(version, sizeof(version) - 1);
    zrepl_active = 0;

    initDs18b20();

    printf("test\r\n");
    GPIO_PinModeSet(DS18B20_PORT, DS18B20_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

    /* Infinite blink loop */
    float temp=0;
    while (1)
    {
        Delay(1000);
        toggleLed();

        temp=DS18B20_ReadTemperaturef();
        printf("helloworld:%f\r\n",temp);
    }
}



