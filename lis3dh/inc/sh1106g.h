#ifndef __SH1106G_H__
#define __SH1106G_H__

#include "oled_interface.h"


void sh1106g_init(void);
void sh1106g_setpos(unsigned char x,unsigned char y);
void sh1106g_fill(unsigned char fill_data);
void sh1106g_cls(void);
void sh1106g_on(void);
void sh1106g_off(void);
void sh1106g_showstr(unsigned char x, unsigned char y, unsigned char *ch, unsigned char TextSize);
void sh1106g_showcn(unsigned char x, unsigned char y, unsigned char N);
void sh1106g_drawbmp(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif
