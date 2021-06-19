//EFM32 button test

#include "config.h"
#include "InitDevice.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "retargetserial.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_rmu.h"
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
 * @brief GPIO Even IRQ for pushbuttons on even-numbered pins
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
    // Clear all even pin interrupt flags
    GPIO_IntClear(0x5555);

    // Toggle LED0
    printf("key1\r\n");
}

/**************************************************************************//**
 * @brief GPIO Odd IRQ for pushbuttons on odd-numbered pins
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
    // Clear all odd pin interrupt flags
    GPIO_IntClear(0xAAAA);

    // Toggle LED01
    printf("key2\r\n");
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
    printf("reset reason:%ld\r\n",rstCause);
    RMU_ResetCauseClear();


    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

    /* Initialize LED driver */
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

    GPIO_PinOutSet(LED_PORT, LED_PIN);


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


    /* Infinite blink loop */
    while (1)
    {
        Delay(1000);
        GPIO_PinOutToggle(LED_PORT, LED_PIN);
        //printf("helloworld\r\n");
    }
}



