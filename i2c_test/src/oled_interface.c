#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "oled_interface.h"


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
        printf("trans failed:%d\r\n",result);
    }
    return result;

}

void WriteCmd(unsigned char I2C_Command)
{
    I2C_TransferReturn_TypeDef result;
	result = i2cWriteByte(I2C0,OLED_ADDRESS,0x00,I2C_Command);
	if(0 != result)
	{
		printf("WriteCmd:%d\r\n",result);
	}

}
void WriteDat(unsigned char I2C_Data)
{
    I2C_TransferReturn_TypeDef result;
	result = i2cWriteByte(I2C0,OLED_ADDRESS,0x40,I2C_Data);
	if(0 != result)
		{
			printf("WriteDat:%d\r\n",result);
		}
}
