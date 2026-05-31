/*
 * cryotimer.c
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */
#include <stdio.h>
#include "em_cryotimer.h"
#include "em_cmu.h"


void CRYOTIMER_IRQHandler(void)
{
  // Acknowledge the interrupt
  uint32_t flags = CRYOTIMER_IntGet();
  CRYOTIMER_IntClear(flags);
  // Put a barrier here to ensure interrupts are not retriggered. See note above
  __DSB();
  printf("%s\r\n",__FUNCTION__);
}


void initCryotimer(void)
{
	CMU_ClockEnable(cmuClock_CRYOTIMER, true);
	// Enable Cryotimer interrupts
	CRYOTIMER_IntEnable(CRYOTIMER_IF_PERIOD);
	NVIC_EnableIRQ(CRYOTIMER_IRQn);
}
