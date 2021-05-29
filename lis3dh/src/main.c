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
#include "em_i2c.h"
#include "sh1106g.h"
#include "lis3dh.h"
#include "i2c_interface.h"



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
    printf("reset reason:%ld\r\n",rstCause);
    RMU_ResetCauseClear();


    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

    /* Initialize LED driver */
    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

    GPIO_PinOutSet(LED_PORT, LED_PIN);


    for(int i=0;i<256;i++)
    {
        uint8_t value;
        I2C_TransferReturn_TypeDef result = i2cReadByte(I2C0,i,0x00,&value);
        if(result == i2cTransferDone)
        {
            printf("ok---------------0x%x:%d:%d\r\n",i,result,value);
        }
        else
        {
            //sprintf("0x%x:%d\r\n",i,result);
        }
    }


    sh1106g_init();
    sh1106g_cls();
    /*
    sh1106g_fill(0x0f);
    sh1106g_showstr(0,1,"1234567890123406",1);
    sh1106g_showstr(0,2,"1239567890123457",1);
    sh1106g_showstr(0,3,"5234567890123455",1);
    sh1106g_showstr(0,4,"1237567890123454",1);
    sh1106g_showstr(0,5,"3234567890123426",1);
    sh1106g_showstr(0,6,"1234547890123456",1);
    sh1106g_showstr(0,7,"1237567890123459",1);
    sh1106g_showstr(0,8,"3234567890623465",1);
    */

    lis3dh_init();



    /* Infinite blink loop */
    while (1)
    {
        //Delay(10);
        GPIO_PinOutToggle(LED_PORT, LED_PIN);
        //printf("helloworld\r\n");
        //read_value();
        //uint8_t value;
        //I2C_TransferReturn_TypeDef result = i2cReadByte(I2C0,ADDRESS_LIS3DH,0x0f,&value);
        //printf("ok---------------%d:0x%x\r\n",result,value);
        read_value();
        getTemp();
    }
}



