/*
 * letimer0.c
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */


#include "letimer0.h"

void LETIMER0_IRQHandler(void)
{

}

void initLetimer(void)
{
	// Enable clock to the LE modules interface
	CMU_ClockEnable(cmuClock_HFLE, true);

	  // Select LFXO for the LETIMER
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
	CMU_ClockEnable(cmuClock_LETIMER0, true);



	LETIMER_Enable(LETIMER0,true);
}
