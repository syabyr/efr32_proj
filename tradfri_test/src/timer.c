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

void initTimer1()
{

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
