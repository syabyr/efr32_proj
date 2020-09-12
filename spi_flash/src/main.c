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


    //SPI test
#define TX_BUFFER_SIZE   10
#define RX_BUFFER_SIZE   TX_BUFFER_SIZE

    uint8_t TxBuffer[TX_BUFFER_SIZE] = {0x9F, 0x00, 0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    uint32_t TxBufferIndex = 0;

    uint8_t RxBuffer[RX_BUFFER_SIZE] = {0};
    uint32_t RxBufferIndex = 0;

    GPIO_PinOutClear(gpioPortB, 11);
    for(int i=0;i<4;i++)
    {
        RxBuffer[i]=USART_SpiTransfer(USART1, TxBuffer[i]);
    }
    GPIO_PinOutSet(gpioPortB, 11);
    printf("JEDEC ID: %x %x %x.\r\n",RxBuffer[1],RxBuffer[2],RxBuffer[3]);


    /* Infinite blink loop */
    while (1)
    {
        Delay(1000);
        GPIO_PinOutToggle(LED_PORT, LED_PIN);
        printf("helloworld\r\n");
    }
}



