/*
 * wdg.c
 *
 *  Created on: May 10, 2020
 *      Author: mybays
 */
#include <stdio.h>
#include <em_wdog.h>

void WDOG0_IRQHandler(void)
{
	WDOG_Feed();
	uint32_t wdogFlag = WDOGn_IntGet(WDOG0);
	WDOGn_IntClear(WDOG0,wdogFlag);
	printf("%s\r\n",__FUNCTION__);
}

void initWDOG(void)
{
	WDOGn_Enable(WDOG0,true);
	WDOGn_IntEnable(WDOG0,WDOG_IEN_WARN);
}
