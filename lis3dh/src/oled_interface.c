#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "oled_interface.h"
#include "i2c_interface.h"




void WriteCmd(unsigned char I2C_Command)
{
    I2C_TransferReturn_TypeDef result;
	result = i2cWriteByte(I2C0,OLED_ADDRESS,0x00,I2C_Command);
	if(0 != result)
	{
		//printf("WriteCmd:%d\r\n",result);
	}

}
void WriteDat(unsigned char I2C_Data)
{
    I2C_TransferReturn_TypeDef result;
	result = i2cWriteByte(I2C0,OLED_ADDRESS,0x40,I2C_Data);
	if(0 != result)
	{
	    //printf("WriteDat:%d\r\n",result);
	}
}
