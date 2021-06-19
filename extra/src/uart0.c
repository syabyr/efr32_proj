/*
 * uart0.c
 *
 *  Created on: May 15, 2020
 *      Author: mybays
 */

#include "em_gpio.h"
#include "em_usart.h"
#include "stdio.h"
#include "retargetserial.h"

#include "uart0.h"

void initUart0()
{
	    /* Pin PB14 is configured to Input enabled */
    GPIO_PinModeSet(USART_RX_PORT, USART_RX_PIN, gpioModeInput, 0);

    /* Pin PB15 is configured to Push-pull */
    GPIO_PinModeSet(USART_TX_PORT, USART_TX_PIN, gpioModePushPull, 0);



	RETARGET_SerialInit();
	RETARGET_ReadChar();

	USART0_enter_DefaultMode_from_RESET();
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
			| USART_ROUTELOC0_CLKLOC_LOC0;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CLKPEN);

	/* Disable CS pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_CSLOC_MASK))
			| USART_ROUTELOC0_CSLOC_LOC0;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CSPEN);

	/* Disable CTS pin */
	USART0->ROUTELOC1 = (USART0->ROUTELOC1 & (~_USART_ROUTELOC1_CTSLOC_MASK))
			| USART_ROUTELOC1_CTSLOC_LOC0;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_CTSPEN);

	/* Disable RTS pin */
	USART0->ROUTELOC1 = (USART0->ROUTELOC1 & (~_USART_ROUTELOC1_RTSLOC_MASK))
			| USART_ROUTELOC1_RTSLOC_LOC0;
	USART0->ROUTEPEN = USART0->ROUTEPEN & (~USART_ROUTEPEN_RTSPEN);

	/* Set up RX pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_RXLOC_MASK))
			| USART_RX_LOCATION;
	USART0->ROUTEPEN = USART0->ROUTEPEN | USART_ROUTEPEN_RXPEN;

	/* Set up TX pin */
	USART0->ROUTELOC0 = (USART0->ROUTELOC0 & (~_USART_ROUTELOC0_TXLOC_MASK))
			| USART_TX_LOCATION;
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