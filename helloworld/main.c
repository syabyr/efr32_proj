//EFM32 blink test

#ifndef LED_PIN
#define LED_PIN     13
#endif
#ifndef LED_PORT
#define LED_PORT    gpioPortB
#endif

#define USART_TX_PORT gpioPortB
#define USART_TX_PIN 15
#define USART_TX_LOCATION 10 // ? found in af_pins.h somehow
#define USART_RX_PORT gpioPortB
#define USART_RX_PIN 14
#define USART_RX_LOCATION 8 // ?

#define USART USART1
#define USART_CLOCK  cmuClock_USART1


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


extern void USART0_enter_DefaultMode_from_RESET(void) {

    // $[USART_InitAsync]
    USART_InitAsync_TypeDef initasync = USART_INITASYNC_DEFAULT;

    initasync.enable = usartDisable;
    initasync.baudrate = 115200;
    initasync.databits = usartDatabits8;
    initasync.parity = usartNoParity;
    initasync.stopbits = usartStopbits1;
    initasync.oversampling = usartOVS16;
#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
    initasync.mvdis = 0;
    initasync.prsRxEnable = 0;
    initasync.prsRxCh = 0;
#endif

    USART_InitAsync(USART0, &initasync);
    // [USART_InitAsync]$

    // $[USART_InitSync]
    // [USART_InitSync]$

    // $[USART_InitPrsTrigger]
    USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

    initprs.rxTriggerEnable = 0;
    initprs.txTriggerEnable = 0;
    initprs.prsTriggerChannel = usartPrsTriggerCh0;

    USART_InitPrsTrigger(USART0, &initprs);
    // [USART_InitPrsTrigger]$

    // $[USART_InitIO]
    /* Disable CLK pin */
    USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_CLKLOC_MASK))
            | USART_ROUTELOC0_CLKLOC_LOC4;
    USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CLKPEN);

    /* Disable CS pin */
    USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK))
            | USART_ROUTELOC0_CSLOC_LOC3;
    USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CSPEN);

    /* Disable CTS pin */
    USART0->ROUTELOC1 = (USART0->ROUTELOC1 & (~_USART_ROUTELOC1_CTSLOC_MASK))
            | USART_ROUTELOC1_CTSLOC_LOC2;
    USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CTSPEN);

    /* Disable RTS pin */
    USART0->ROUTELOC1 = (USART0->ROUTELOC1 & (~_USART_ROUTELOC1_RTSLOC_MASK))
            | USART_ROUTELOC1_RTSLOC_LOC1;
    USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_RTSPEN);

    /* Set up RX pin */
    USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_RXLOC_MASK))
            | USART_ROUTELOC0_RXLOC_LOC8;
    USART0->ROUTEPEN = USART0->ROUTEPEN | USART_ROUTEPEN_RXPEN;

    /* Set up TX pin */
    USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_TXLOC_MASK))
            | USART_ROUTELOC0_TXLOC_LOC10;
    USART0->ROUTEPEN = USART0->ROUTEPEN | USART_ROUTEPEN_TXPEN;

    // [USART_InitIO]$

    // $[USART_Misc]
    /* Disable CTS */
    USART0->CTRLX = USART0->CTRLX & (~USART_CTRLX_CTSEN);
    /* Set CTS active low */
    USART0->CTRLX = USART0->CTRLX & (~USART_CTRLX_CTSINV);
    /* Set RTS active low */
    USART0->CTRLX = USART0->CTRLX & (~USART_CTRLX_RTSINV);
    /* Set CS active low */
    USART0->CTRL = USART0->CTRL & (~USART_CTRL_CSINV);
    /* Set TX active high */
    USART0->CTRL = USART0->CTRL & (~USART_CTRL_TXINV);
    /* Set RX active high */
    USART0->CTRL = USART0->CTRL & (~USART_CTRL_RXINV);
    // [USART_Misc]$

    // $[USART_Enable]

    /* Enable USART if opted by user */
    USART_Enable(USART0, usartEnable);
    // [USART_Enable]$

}

//================================================================================
// PORTIO_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTIO_enter_DefaultMode_from_RESET(void) {

    // $[Port A Configuration]
    // [Port A Configuration]$

    // $[Port B Configuration]

    /* Pin PB11 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortB, 11, gpioModePushPull, 0);

    /* Pin PB14 is configured to Input enabled */
    GPIO_PinModeSet(gpioPortB, 14, gpioModeInput, 0);

    /* Pin PB15 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 0);
    // [Port B Configuration]$

    // $[Port C Configuration]

    /* Pin PC10 is configured to Input enabled with pull-up */
    GPIO_PinModeSet(gpioPortC, 10, gpioModeInputPull, 1);
    // [Port C Configuration]$

    // $[Port D Configuration]

    /* Pin PD13 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 0);

    /* Pin PD14 is configured to Input enabled */
    GPIO_PinModeSet(gpioPortD, 14, gpioModeInput, 0);

    /* Pin PD15 is configured to Push-pull */
    GPIO_PinModeSet(gpioPortD, 15, gpioModePushPull, 0);
    // [Port D Configuration]$

    // $[Port E Configuration]
    // [Port E Configuration]$

    // $[Port F Configuration]
    // [Port F Configuration]$

}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
    CHIP_Init();

    CMU_ClockEnable(cmuClock_GPIO, true);

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

    USART0_enter_DefaultMode_from_RESET();
    PORTIO_enter_DefaultMode_from_RESET();
    /* Initialize LED driver */
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

    GPIO_PinOutSet(LED_PORT, LED_PIN);

    RETARGET_SerialInit();
  RETARGET_ReadChar();


    USART0_enter_DefaultMode_from_RESET();

    printf("test\r\n");

    /* Infinite blink loop */
    while (1)
    {
        Delay(1000);
        GPIO_PinOutToggle(LED_PORT, LED_PIN);
        printf("helloworld\r\n");
    }
}



