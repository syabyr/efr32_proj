#ifndef __LIS3DH_H__
#define __LIS3DH_H__

#include "oled_interface.h"

#define ADDRESS_LIS3DH 0x32


#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define STATUS_REG 0x27
#define OUT_X_L 0x28

#define TEMP_CFG_REG 0x1F
#define OUT_ADC3_L 0x0C
#define OUT_ADC3_H 0x0D

#define ACT_DUR 0x3F



int lis3dh_init(void);

void read_value(void);

int8_t getTemp(void);
#endif