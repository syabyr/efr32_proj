/*
 * radio.h
 *
 *  Created on: May 16, 2020
 *      Author: mybays
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include "em_gpio.h"

#ifndef DS18B20_PIN
#define DS18B20_PIN     0
#endif
#ifndef DS18B20_PORT
#define DS18B20_PORT    gpioPortA
#endif


#define DS18B20_DQ_OUT          GPIO_PinModeSet(DS18B20_PORT, DS18B20_PIN, gpioModePushPull, 0)
#define DS18B20_DQ_IN           GPIO_PinModeSet(DS18B20_PORT, DS18B20_PIN, gpioModeInputPull, 1)
#define DS18B20_DQ_HIGH         GPIO_PinOutSet(DS18B20_PORT, DS18B20_PIN)
#define DS18B20_DQ_LOW          GPIO_PinOutClear(DS18B20_PORT, DS18B20_PIN)
#define DS18B20_DQ_PULL_UP      GPIO_PinModeSet(DS18B20_PORT, DS18B20_PIN, gpioModeInputPull, 1)
//#define DS18B20_DQ_FLOATING     GPIOC->CR1 &=  ~(1<<3)  //??
#define DS18B20_DQ_PUSH_PULL    GPIO_PinModeSet(DS18B20_PORT, DS18B20_PIN, gpioModePushPull, 1)
//#define DS18B20_DQ_OPEN_DRAIN   GPIOC->CR1 &= ~(1<<3)   //??
#define DS18B20_DQ_VALUE        GPIO_PinInGet(DS18B20_PORT, DS18B20_PIN)


//commands
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define DS18B20_CMD_SEARCHROM 0xf0
#define DS18B20_CMD_READROM 0x33
#define DS18B20_CMD_MATCHROM 0x55
#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_ALARMSEARCH 0xec


void initDs18b20(void);

void DS18B20_Init(void);
void DS18B20_WriteByte(unsigned char _data);
unsigned char DS18B20_ReadByte(void);
uint16_t DS18B20_ReadTemperature(void);
float DS18B20_ReadTemperaturef(void);

#endif /* INC_DS18B20_H_ */