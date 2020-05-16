/*
 * timer.c
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */
#include <stdio.h>
#include "timer.h"
#include "em_cmu.h"
#include "em_timer.h"

uint16_t topValue;

void TIMER0_IRQHandler(void)
{
	printf("%s\r\n",__FUNCTION__);
}

void TIMER1_IRQHandler(void)
{
	printf("%s\r\n",__FUNCTION__);
}


void initTimer0()
{
	topValue = CMU_ClockFreqGet(cmuClock_TIMER0) / 1000000;
	printf("Timer0:%ld\r\n",CMU_ClockFreqGet(cmuClock_TIMER0));
}


extern void TIMER1_enter_DefaultMode_from_RESET(void) {

    // $[TIMER1 I/O setup]
    /* Set up CC0 */
    TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC0LOC_MASK))
                        | TIMER_ROUTELOC0_CC0LOC_LOC0;
    TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC0PEN);
    /* Set up CC1 */
    TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC1LOC_MASK))
                        | TIMER_ROUTELOC0_CC1LOC_LOC0;
    TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC1PEN);
    /* Set up CC2 */
    TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC2LOC_MASK))
                        | TIMER_ROUTELOC0_CC2LOC_LOC4;
    TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC2PEN);
    /* Set up CC3 */
    TIMER1->ROUTELOC0 = (TIMER1->ROUTELOC0 & (~_TIMER_ROUTELOC0_CC3LOC_MASK))
                        | TIMER_ROUTELOC0_CC3LOC_LOC3;
    TIMER1->ROUTEPEN = TIMER1->ROUTEPEN & (~TIMER_ROUTEPEN_CC3PEN);
    // [TIMER1 I/O setup]$

    // $[TIMER1 initialization]
    TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

    init.enable = 1;
    init.debugRun = 0;
    init.dmaClrAct = 0;
    init.sync = 0;
    init.clkSel = timerClkSelHFPerClk;
    init.prescale = timerPrescale1;
    init.fallAction = timerInputActionNone;
    init.riseAction = timerInputActionNone;
    init.mode = timerModeUp;
    init.quadModeX4 = 0;
    init.oneShot = 0;
    init.count2x = 0;
    init.ati = 0;
    TIMER_Init(TIMER1, &init);
    // [TIMER1 initialization]$

    // $[TIMER1 CC0 init]
    TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

    initCC0.prsInput = false;
    initCC0.prsSel = timerPRSSELCh0;
    initCC0.edge = timerEdgeRising;
    initCC0.mode = timerCCModeOff;
    initCC0.eventCtrl = timerEventEveryEdge;
    initCC0.filter = 0;
    initCC0.cofoa = timerOutputActionNone;
    initCC0.cufoa = timerOutputActionNone;
    initCC0.cmoa = timerOutputActionNone;
    initCC0.coist = 0;
    initCC0.outInvert = 0;
    TIMER_InitCC(TIMER1, 0, &initCC0);
    // [TIMER1 CC0 init]$

    // $[TIMER1 CC1 init]
    TIMER_InitCC_TypeDef initCC1 = TIMER_INITCC_DEFAULT;

    initCC1.prsInput = false;
    initCC1.prsSel = timerPRSSELCh0;
    initCC1.edge = timerEdgeRising;
    initCC1.mode = timerCCModeOff;
    initCC1.eventCtrl = timerEventEveryEdge;
    initCC1.filter = 0;
    initCC1.cofoa = timerOutputActionNone;
    initCC1.cufoa = timerOutputActionNone;
    initCC1.cmoa = timerOutputActionNone;
    initCC1.coist = 0;
    initCC1.outInvert = 0;
    TIMER_InitCC(TIMER1, 1, &initCC1);
    // [TIMER1 CC1 init]$

    // $[TIMER1 CC2 init]
    TIMER_InitCC_TypeDef initCC2 = TIMER_INITCC_DEFAULT;

    initCC2.prsInput = false;
    initCC2.prsSel = timerPRSSELCh0;
    initCC2.edge = timerEdgeRising;
    initCC2.mode = timerCCModeOff;
    initCC2.eventCtrl = timerEventEveryEdge;
    initCC2.filter = 0;
    initCC2.cofoa = timerOutputActionNone;
    initCC2.cufoa = timerOutputActionNone;
    initCC2.cmoa = timerOutputActionNone;
    initCC2.coist = 0;
    initCC2.outInvert = 0;
    TIMER_InitCC(TIMER1, 2, &initCC2);
    // [TIMER1 CC2 init]$

    // $[TIMER1 CC3 init]
    TIMER_InitCC_TypeDef initCC3 = TIMER_INITCC_DEFAULT;

    initCC3.prsInput = false;
    initCC3.prsSel = timerPRSSELCh0;
    initCC3.edge = timerEdgeRising;
    initCC3.mode = timerCCModeOff;
    initCC3.eventCtrl = timerEventEveryEdge;
    initCC3.filter = 0;
    initCC3.cofoa = timerOutputActionNone;
    initCC3.cufoa = timerOutputActionNone;
    initCC3.cmoa = timerOutputActionNone;
    initCC3.coist = 0;
    initCC3.outInvert = 0;
    TIMER_InitCC(TIMER1, 3, &initCC3);
    // [TIMER1 CC3 init]$

}

void initTimer1()
{
    TIMER1_enter_DefaultMode_from_RESET();
}


void _delay_us(int us)
{
	uint16_t us1= us*topValue;
	TIMER1->CNT=0;
	while(TIMER1->CNT <(uint16_t)us1)
	{
		;
	}
}

void _delay_ms(int ms)
{
	for (; ms; --ms)
	{
	    _delay_us(1000);
	}
}
