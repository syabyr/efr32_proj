#include "em_device.h"
#include "em_chip.h"
#include "em_usart.h"
#include "em_rmu.h"
#include "em_cmu.h"
#include "em_wdog.h"
#include "InitDevice.h"

#include "stdio.h"
#include "retargetserial.h"

#include "led.h"
#include "spi.h"
#include "rtcc.h"
#include "cryotimer.h"
#include "timer.h"
#include "wdg.h"


#define EM4WU_EM4WUEN_NUM   (10)                       // PB1 is EM4WUEN pin 1
#define EM4WU_EM4WUEN_MASK  (1 << EM4WU_EM4WUEN_NUM)
#define EM4_RSTCAUSE_MASK	RMU_RSTCAUSE_EM4RST


void em4init()
{
	GPIO_PinModeSet(gpioPortC, 10, gpioModeInputPullFilter, 1);
	GPIO_EM4EnablePinWakeup(12 << _GPIO_EM4WUEN_EM4WUEN_SHIFT, 0);
}


void SysTick_Handler(void)
{
	WDOG_Feed();
}


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  initLed();
  //em4init();

  RETARGET_SerialInit();
  RETARGET_ReadChar();

  enter_DefaultMode_from_RESET();

  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

  printf("\r\nhelloworld:%f.\r\n",100.02);
  printf("Silicon Labs UART Code example!\r\f");

  // Get the last Reset Cause
  uint32_t rstCause = RMU_ResetCauseGet();
  printf("reset reason:%ld\r\n",rstCause);
  RMU_ResetCauseClear();

  initTimer0();
  initWDOG();

  /*
  if (rstCause == EM4_RSTCAUSE_MASK)
  {
    toggleLed();
  }
  else
  {
    for (volatile uint32_t delay = 0; delay < 0xFFF; delay++);
    EMU_EnterEM4();
  }
  */



  spiTest();

  //testRtcc();
  initCryotimer();

  /* Infinite loop */
  while (1)
  {
	  /*
	  for(int i=0;i<65536;i++)
	  {
		  for(int j=0;j<653;j++)
		  {
			  ;
		  }
	  }*/
	  _delay_ms(2000);
	  toggleLed();
	  WDOG_Feed();
	  printf("helloworld.\r\n");
  }
}
