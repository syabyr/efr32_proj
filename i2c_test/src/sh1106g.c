#include "sh1106g.h"
#include "bmp.h"
#include "codetab.h"


void sh1106g_init(void)
{
	//delay_ms(100); //这里的延时很重要

	WriteCmd(0xAE); //display off
	WriteCmd(0xD5);	//Set Memory Addressing Mode
	WriteCmd(0x80);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xA8);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0x3F);	//Set COM Output Scan Direction
	WriteCmd(0xD3); //---set low column address
	WriteCmd(0x00); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0xAD); //--set contrast control register
	WriteCmd(0x8B); //亮度调节 0x00~0xff
	WriteCmd(0x32); //--set segment re-map 0 to 127
	WriteCmd(0xA1); //--set normal display
	WriteCmd(0xC8); //--set multiplex ratio(1 to 64)
	WriteCmd(0xDA); //
	WriteCmd(0x12); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0x81); //-set display offset
	WriteCmd(0xCC); //-not offset
	WriteCmd(0xD9); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0x22); //--set divide ratio
	WriteCmd(0xDB); //--set pre-charge period
	WriteCmd(0x40); //
	WriteCmd(0xA4); //--set com pins hardware configuration
	WriteCmd(0xA6);
	WriteCmd(0xAF); //--set vcomh
}

void sh1106g_setpos(unsigned char x,unsigned char y)
{
	x=x+16;
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

void sh1106g_fill(unsigned char fill_data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x11);		//low column start address
		WriteCmd(0x01);		//high column start address
		for(n=0;n<97;n++)
		{
			WriteDat(fill_data);
		}
	}
}
void sh1106g_cls(void)
{
	sh1106g_fill(0x00);
}
void sh1106g_on(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}
void sh1106g_off(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}
void sh1106g_showstr(unsigned char x, unsigned char y, unsigned char *ch, unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	y = y - 1;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				sh1106g_setpos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				sh1106g_setpos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				sh1106g_setpos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}
void sh1106g_showcn(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	sh1106g_setpos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	sh1106g_setpos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}
void sh1106g_drawbmp(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y,i,k;

	if(y1%8==0)
		y = y1/8;
	else
		y = y1/8 + 1;


	for(i=0;i<y;i++)
	{
		sh1106g_setpos(0,i);
		for(j=x0;j<(x1-1);j++)
		{
			WriteDat(BMP[i * x1 + j]);//原来是j++,做了两次加法,所以最后只画了64的长度
			//delay_ms(10);
		}
	}
}

