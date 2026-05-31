/*
 * rtcc.c
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */
#include "stdio.h"
#include "em_rtcc.h"
#include "em_cmu.h"
#include "led.h"

int start = -1;


void RTCC_IRQHandler(void)
{
	// Read the interrupt source
	uint32_t rtccFlag = RTCC_IntGet();
	RTCC_IntClear(rtccFlag);
	toggleLed();
	printf("%s\r\n",__FUNCTION__);

}


void rtccSetup(int start_time, int start_date, int alarmh_start, int alarmd_start)
{

	// Turn on the clock for the RTCC
	CMU_ClockEnable(cmuClock_HFLE, true);
	CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFRCO);
	CMU_ClockEnable(cmuClock_RTCC, true);

	// Set current date and time
	RTCC_DateSet(start_date);
	RTCC_TimeSet(start_time);

	RTCC_CCChConf_TypeDef compare = RTCC_CH_INIT_COMPARE_DEFAULT;

	// Initialise RTCC compare with a date, the date when interrupt will occur
	RTCC_ChannelInit(1, &compare);
	RTCC_ChannelDateSet(1, alarmd_start);
	RTCC_ChannelTimeSet(1,alarmh_start);

	// Set channel 1 to cause an interrupt
	RTCC_IntEnable(RTCC_IEN_CC1);
	NVIC_ClearPendingIRQ(RTCC_IRQn);
	NVIC_EnableIRQ(RTCC_IRQn);

	// Start counter after all initialisations are complete
	RTCC_Enable(true);
}




void testRtcc()
{
	  // Convert the strings received into hex for passing to the RTCC
	  int start_time = 1638400;
	  int start_date = 538969360;
	  int alarmh_start = 1638448;
	  int alarmd_start = 538969360;

	  rtccSetup(start_time, start_date,alarmh_start,alarmd_start);
	  printf("rtccSetup finished.\r\n");
}
