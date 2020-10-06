//
// Created by mybays on 2020/10/5.
//
#include "i2c_interface.h"

I2C_TransferReturn_TypeDef i2cReadByte(I2C_TypeDef *i2c,uint16_t addr,uint8_t command,uint8_t *val)
{
    I2C_TransferSeq_TypeDef    seq;
    I2C_TransferReturn_TypeDef result;
    uint8_t i2c_write_data[1]={0};
    uint8_t i2c_read_data[1]={0};

    seq.addr = addr;
    seq.flags = I2C_FLAG_WRITE_READ;
    i2c_write_data[0] = command;
    seq.buf[0].data   = i2c_write_data;
    seq.buf[0].len    = 1;

    seq.buf[1].data = i2c_read_data;
    seq.buf[1].len  = 1;

    result = I2C_TransferInit(i2c, &seq);

    while(result == i2cTransferInProgress)
    {
        result = I2C_Transfer(i2c);
    }

    if (result != i2cTransferDone)
    {
        //printf("trans failed:%d\r\n",result);
        return result;
    }

    if(NULL != val)
    {
        *val = i2c_read_data[0];
    }
    return result;

}


I2C_TransferReturn_TypeDef i2cWriteByte(I2C_TypeDef *i2c,uint16_t addr,uint8_t command,uint8_t val)
{
    I2C_TransferSeq_TypeDef    seq;
    I2C_TransferReturn_TypeDef result;
    uint8_t i2c_write_data[1]={0};
    uint8_t i2c_read_data[1]={0};

    seq.addr = addr;
    seq.flags = I2C_FLAG_WRITE;
    i2c_write_data[0] = command;
    i2c_write_data[1] = val;
    seq.buf[0].data   = i2c_write_data;
    seq.buf[0].len    = 2;

    seq.buf[1].data = i2c_read_data;
    seq.buf[1].len  = 1;

    result = I2C_TransferInit(i2c, &seq);

    while(result == i2cTransferInProgress)
    {
        result = I2C_Transfer(i2c);
    }

    if (result != i2cTransferDone)
    {
        //printf("trans failed:%d\r\n",result);
    }
    return result;

}