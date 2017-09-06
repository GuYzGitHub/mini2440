#include "spi.h"
#include "s3c2440.h"
#include "oled_font.h"

void OLEDset_D_C(char val);
void OLED_CS(unsigned char val);
void OLEDWriteCmd(unsigned char cmd);
void OLEDWriteDat(unsigned char dat);
void oledSetPos(int page, int col);
void oled_putChar(int page, int col, char c);

void oled_clear(int bit)
{
	int page, j;
	for(page=0; page < 8; page++)
	{
		oledSetPos(page, 0);
		for(j=0; j < 127; j++)
		{
			if(bit == 1)
			{
				OLEDWriteDat(0xff);
			}
			if(bit == 0)
			{
				OLEDWriteDat(0x00);
			}
		}
	}
}

void oled_init(void)
{
    /* 向OLED发命令以初始化 */
    OLEDWriteCmd(0xAE); /*display off*/ 
    OLEDWriteCmd(0x00); /*set lower column address*/ 
    OLEDWriteCmd(0x10); /*set higher column address*/ 
    OLEDWriteCmd(0x40); /*set display start line*/ 
    OLEDWriteCmd(0xB0); /*set page address*/ 
    OLEDWriteCmd(0x81); /*contract control*/ 
    OLEDWriteCmd(0x66); /*128*/ 
    OLEDWriteCmd(0xA1); /*set segment remap*/ 
    OLEDWriteCmd(0xA6); /*normal / reverse*/ 
    OLEDWriteCmd(0xA8); /*multiplex ratio*/ 
    OLEDWriteCmd(0x3F); /*duty = 1/64*/ 
    OLEDWriteCmd(0xC8); /*Com scan direction*/ 
    OLEDWriteCmd(0xD3); /*set display offset*/ 
    OLEDWriteCmd(0x00); 
    OLEDWriteCmd(0xD5); /*set osc division*/ 
    OLEDWriteCmd(0x80); 
    OLEDWriteCmd(0xD9); /*set pre-charge period*/ 
    OLEDWriteCmd(0x1f); 
    OLEDWriteCmd(0xDA); /*set COM pins*/ 
    OLEDWriteCmd(0x12); 
    OLEDWriteCmd(0xdb); /*set vcomh*/ 
    OLEDWriteCmd(0x30); 
    OLEDWriteCmd(0x8d); /*set charge pump enable*/ 
    OLEDWriteCmd(0x14); 

    OLEDWriteCmd(0x20); 
    OLEDWriteCmd(0x02); 

	oled_clear(0);

    OLEDWriteCmd(0xAF); /*display ON*/    
}


void OLEDset_D_C(char val)
{

/*	D/C引脚为1时OLED接收数据，为0时接收命令 */

	if(val == 'D')
	{
		GPFDAT |= (1<<3);
	}
	else if(val == 'C')
	{
		GPFDAT &= ~(1<<3);
	}
}

void OLED_CS(unsigned char val)
{
/* GPG1 OLED_CSn    OLED低电平片选 */
	if(val)
	{
		GPGDAT |= (1<<1);
	}
	else
	{
		GPGDAT &= ~(1<<1);
	}
}

void OLEDWriteCmd(unsigned char cmd)
{
	OLED_CS(0);				//片选OLED
	OLEDset_D_C('C');			//设置命令模式
	spi_send_Byte(cmd);		//发送命令
	OLEDset_D_C('D');			//恢复数据模式
	OLED_CS(1);				//取消片选OLED
}

void OLEDWriteDat(unsigned char dat)
{
	OLED_CS(0);				//片选OLED
	OLEDset_D_C('D');			//设置数据模式
	spi_send_Byte(dat);		//发送数据
	OLED_CS(1);				//取消片选OLED
}

void oledSetPos(int page, int col)
{
	 OLEDWriteCmd(0xB0 + page); /* page address */
	 OLEDWriteCmd(col & 0xf);   /* Lower Column Start Address */
	 OLEDWriteCmd(0x10 + (col >> 4));   /* Lower Higher Start Address */
}

void oled_putChar(int page, int col, char c)
{

	int i = 0;
	/* 定位字符 */
	const unsigned char *dots = oled_font_8x16[c - ' '];

	/* 发送第一个page数据 */
	oledSetPos(page, col);
	for(i=0; i<8; i++)
	{
		OLEDWriteDat(dots[i]);
	}
	/* 发送第二个page数据 */
	oledSetPos(page+1, col);
	for(i=0; i<8; i++)
	{
		OLEDWriteDat(dots[i+8]);
	}
}

void print_oled(int page, int col, char *str)
{
/* page: 0-7
 * col : 0-127
 * cahr: 8*16像素
 * OLED: 127×64
 */
	int i;
	for(i=0; str[i] != '\0'; i++)
	{
		oled_putChar(page, col, str[i]);
		col += 8;
		if(col > 127)
		{
			col = 0;
			page += 2;
		}
	}
}
