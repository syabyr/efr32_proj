#include "lis3dh.h"
#include "i2c_interface.h"
#include "sh1106g.h"

extern void Delay(uint32_t dlyTicks);

int lis3dh_init(void)
{
    //确定
    uint8_t value;
    I2C_TransferReturn_TypeDef result;

    result = i2cReadByte(I2C0,ADDRESS_LIS3DH,0x0f,&value);
    //printf("ok---------------%d:0x%x\r\n",result,value);
    if(0 != result)
    {
        return result;
    }
    if(value == 0x33)
    {
        printf("find LS3DH\r\n");
    }
    else
    {
        printf("id error:0x%x\r\n",value);
        return -1;
    }

    result = i2cWriteByte(I2C0,ADDRESS_LIS3DH,CTRL_REG5,0x80);
    if(0 != result)
    {
        printf("WriteCmd:%d\r\n",result);
    }
    Delay(5);


    result = i2cReadByte(I2C0,ADDRESS_LIS3DH,CTRL_REG5,&value);
    printf("CTRL_REG5:%d:0x%x\r\n",result,value);




    result = i2cWriteByte(I2C0,ADDRESS_LIS3DH,CTRL_REG1,0x17);
    if(0 != result)
    {
        printf("WriteCmd:%d\r\n",result);
    }

    result = i2cReadByte(I2C0,ADDRESS_LIS3DH,CTRL_REG1,&value);
    printf("CTRL_REG1:%d:0x%x\r\n",result,value);


    result = i2cWriteByte(I2C0,ADDRESS_LIS3DH,CTRL_REG4,0x80);
    if(0 != result)
    {
        printf("WriteCmd:%d\r\n",result);
    }

    result = i2cReadByte(I2C0,ADDRESS_LIS3DH,CTRL_REG4,&value);
    printf("CTRL_REG4:%d:0x%x\r\n",result,value);

    result = i2cWriteByte(I2C0,ADDRESS_LIS3DH,TEMP_CFG_REG,0xC0);
    if(0 != result)
    {
        printf("WriteCmd:%d\r\n",result);
    }

    result = i2cReadByte(I2C0,ADDRESS_LIS3DH,TEMP_CFG_REG,&value);
    printf("TEMP_CFG_REG:%d:0x%x\r\n",result,value);

    return 0;
}


void read_value()
{
    bool ready = false;
    uint8_t value = 0;
    I2C_TransferReturn_TypeDef result;
    int count=0;
    while( false == ready)
    {
        result = i2cReadByte(I2C0,ADDRESS_LIS3DH,STATUS_REG,&value);
        if(result != 0)
        {
            count ++;
            if(count >= 500)
            {
                printf("read STATUS_REG failed:%d\r\n",result);
                count = 0;
            }
            continue;
        }
        if(value && 1<< 3)
        {
            ready = true;
        }
        Delay(10);
    }
    if(value && 1<<7)
    {
        printf("Some data have been overwritten\r\n");
    }

    //read data
    I2C_TransferSeq_TypeDef    seq;
    uint8_t i2c_write_data[6]={0};
    uint8_t i2c_read_data[6]={0};

    seq.addr = ADDRESS_LIS3DH;
    seq.flags = I2C_FLAG_WRITE_READ;
    i2c_write_data[0] = OUT_X_L|0x80;
    //i2c_write_data[1] = val;
    seq.buf[0].data   = i2c_write_data;
    seq.buf[0].len    = 1;

    seq.buf[1].data = i2c_read_data;
    seq.buf[1].len  = 6;

    result = I2C_TransferInit(I2C0, &seq);

    while(result == i2cTransferInProgress)
    {
        result = I2C_Transfer(I2C0);
    }

    if (result != i2cTransferDone)
    {
        printf("trans failed:%d\r\n",result);
    }
    else
    {
        //printf("ok---------------%d,0x%x:%x,0x%x:%x,0x%x:%x\r\n",result,i2c_read_data[0],i2c_read_data[1],i2c_read_data[2],i2c_read_data[3],i2c_read_data[4],i2c_read_data[5]);

        int16_t outX=(i2c_read_data[1]<<8)|i2c_read_data[0];
        int16_t outY=(i2c_read_data[3]<<8)|i2c_read_data[2];
        int16_t outZ=(i2c_read_data[5]<<8)|i2c_read_data[4];

        int16_t xVal = outX/16;
        int16_t yVal = outY/16;
        int16_t zVal = outZ/16;
        printf("x:%6d,y:%6d,z:%6d\r\n",xVal,yVal,zVal);

        char temp[12]={0};
        sprintf(temp,"X:%6d",xVal);
        sh1106g_showstr(0,1,temp,1);
        sprintf(temp,"Y:%6d",yVal);
        sh1106g_showstr(0,2,temp,1);
        sprintf(temp,"Z:%6d",zVal);
        sh1106g_showstr(0,3,temp,1);
    }
}

int8_t getTemp(void)
{
    //range from -40 °C to +85 °C
    //read data
    I2C_TransferReturn_TypeDef result;
    I2C_TransferSeq_TypeDef    seq;
    uint8_t i2c_write_data[1]={0};
    uint8_t i2c_read_data[2]={0};

    seq.addr = ADDRESS_LIS3DH;
    seq.flags = I2C_FLAG_WRITE_READ;
    i2c_write_data[0] = OUT_ADC3_L|0x80;
    seq.buf[0].data   = i2c_write_data;
    seq.buf[0].len    = 1;

    seq.buf[1].data = i2c_read_data;
    seq.buf[1].len  = 2;

    result = I2C_TransferInit(I2C0, &seq);

    while(result == i2cTransferInProgress)
    {
        result = I2C_Transfer(I2C0);
    }

    if (result != i2cTransferDone)
    {
        printf("trans failed:%d\r\n",result);
    }
    else
    {
        int16_t buff=(i2c_read_data[1]<<8)|i2c_read_data[0];

        printf("temp:%6d\r\n",buff);

    }

    return 0;
}