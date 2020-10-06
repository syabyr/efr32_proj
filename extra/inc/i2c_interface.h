//
// Created by mybays on 2020/10/5.
//

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include <stdio.h>
#include "em_i2c.h"

I2C_TransferReturn_TypeDef i2cReadByte(I2C_TypeDef *i2c,uint16_t addr,uint8_t command,uint8_t *val);
I2C_TransferReturn_TypeDef i2cWriteByte(I2C_TypeDef *i2c,uint16_t addr,uint8_t command,uint8_t val);

#endif //I2C_INTERFACE_H
