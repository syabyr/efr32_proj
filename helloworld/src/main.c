//EFM32 blink test

#ifndef LED_PIN
#define LED_PIN     13
#endif
#ifndef LED_PORT
#define LED_PORT    gpioPortB
#endif


#include "InitDevice.h"

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

    CMU_ClockEnable(cmuClock_GPIO, true);

    RETARGET_SerialInit();
    RETARGET_ReadChar();
    enter_DefaultMode_from_RESET();


    printf("\r\nhelloworld:%f.\r\n",100.02);
    printf("Silicon Labs UART Code example!\r\f");

    // Get the last Reset Cause
    uint32_t rstCause = RMU_ResetCauseGet();
    printf("reset reason:%d\r\n",rstCause);
    RMU_ResetCauseClear();


    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

    /* Initialize LED driver */
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

    GPIO_PinOutSet(LED_PORT, LED_PIN);


    /* Infinite blink loop */
    while (1)
    {
        Delay(1000);
        GPIO_PinOutToggle(LED_PORT, LED_PIN);
        printf("helloworld\r\n");
    }
}



