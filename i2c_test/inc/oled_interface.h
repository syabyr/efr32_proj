#ifndef __OLED_INTERFACE_H__
#define __OLED_INTERFACE_H__

#include "em_i2c.h"

#define OLED_ADDRESS 0x78

void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);

#endif
