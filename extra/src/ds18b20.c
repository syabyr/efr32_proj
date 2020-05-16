/*
 * ds18b20.c
 *
 *  Created on: May 16, 2020
 *      Author: mybays
 */

#include <stdio.h>
#include "ds18b20.h"
#include "timer.h"


void initDs18b20(void)
{
    GPIO_PinModeSet(DS18B20_PORT, DS18B20_PIN, gpioModePushPull, 0);
}



void DS18B20_Init(void)
{
    DS18B20_DQ_OUT;
    DS18B20_DQ_PUSH_PULL;
    DS18B20_DQ_HIGH;
    _delay_us(10);
    DS18B20_DQ_LOW;
    _delay_us(600);     //????

    DS18B20_DQ_IN;
    DS18B20_DQ_PULL_UP;
    _delay_us(100);
    while(DS18B20_DQ_VALUE == 1);
    _delay_us(400);
}

void DS18B20_WriteByte(unsigned char _data)
{
    unsigned char i = 0;

    DS18B20_DQ_OUT;
    for (i = 0; i < 8; i++)
    {
        DS18B20_DQ_LOW;
        _delay_us(2);
        if (_data & 0x01)
        {
            DS18B20_DQ_HIGH;
        }
        _data >>= 1;
        _delay_us(60);
        DS18B20_DQ_HIGH;
    }
}

unsigned char DS18B20_ReadByte(void)
{
    unsigned char i = 0, _data = 0;

    for (i = 0; i < 8; i++)
    {
        DS18B20_DQ_OUT;
        DS18B20_DQ_LOW;
        _delay_us(5);
        _data >>= 1;
        DS18B20_DQ_HIGH;
        DS18B20_DQ_IN;
        if (DS18B20_DQ_VALUE)
        {
            _data |= 0x80;
        }
        DS18B20_DQ_OUT;
        DS18B20_DQ_HIGH;
        _delay_us(60);
    }

    return _data;
}

uint16_t DS18B20_ReadTemperature(void)
{
    unsigned char temp0 = 0;
    unsigned char temp1 = 0;
    uint16_t result;
/*
 *
 *
 *  0x44 is the command to calculate the temperature and save it in the scratchpad.  This takes up to 750 milliseconds.
 *
 *  0xBE is the command to send the contents of of the scratchpad.
 *
 *  What you are sending is "Everybody: Send your Scratchpad".  This only works if you only have one device.
 *
 */
    DS18B20_Init();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0x44);

    DS18B20_Init();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0xbe);

    temp0 = DS18B20_ReadByte();
    temp1 = DS18B20_ReadByte();
    printf("%d:%d\r\n",temp0,temp1);
    result=temp1;
    result = result<<8;
    result |= temp0;

    return result;
}



float DS18B20_ReadTemperaturef(void)
{
    unsigned char temp0 = 0;
    unsigned char temp1 = 0;
    float t = 0;

    DS18B20_Init();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0x44);

    DS18B20_Init();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0xbe);

    temp0 = DS18B20_ReadByte();
    t = (((temp0 & 0xf0) >> 4) + (temp0 & 0x07) * 0.125);
    temp1 = DS18B20_ReadByte();
    t += ((temp1 & 0x0f) << 4);
    printf("%d:%d\r\n",temp0,temp1);

    return t;
}