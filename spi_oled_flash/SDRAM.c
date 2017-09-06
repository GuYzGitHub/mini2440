			/********************
			*		Memory		*
			********************/
#include "s3c2440.h"
#include "LED.h"

/* SDRAM regisers */
#define     MEM_CTL_BASE   (volatile unsigned long*) 0x48000000
#define     SDRAM_BASE      0x30000000

void sdram_set()
{
	volatile unsigned long *p = MEM_CTL_BASE;    //将指针指向内存控制器首地址
    p[0] = 0x22011110;     //BWSCON
    p[1] = 0x00000700;     //BANKCON0
    p[2] = 0x00000700;     //BANKCON1
    p[3] = 0x00000700;     //BANKCON2
    p[4] = 0x00000700;     //BANKCON3  
    p[5] = 0x00000700;     //BANKCON4
    p[6] = 0x00000700;     //BANKCON5
    p[7] = 0x00018005;     //BANKCON6
    p[8] = 0x00018005;     //BANKCON7
                                            /* REFRESH,
                                             * HCLK=12MHz:  0x008C07A3,
                                             * HCLK=100MHz: 0x008C04F4
                                             */ 
    p[9]  = 0x008C04F4;
    p[10] = 0x000000B1;     //BANKSIZE
    p[11] = 0x00000030;     //MRSRB6
    p[12] = 0x00000030;     //MRSRB7
}

void copy_memory(volatile unsigned long* SouAddr,
                 volatile unsigned long* DesAddr,
                 unsigned int size)
{
	unsigned int i;
	for(i=0; i<size; i++)
	{
		DesAddr[i] = SouAddr[i];
	}
	//检测复制是否成功
	for(i=0; i<size; i++)
	{
		if(DesAddr[i] != SouAddr[i])
		{
			error_led(14);
		}
	}
}

