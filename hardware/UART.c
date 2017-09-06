			/********************
			 *    	  UART  	*
			 *******************/
#include "s3c2440.h"

void uart0_set()
{
	GPHCON |= 0xa0;		// GPH2,GPH3用作TXD),RXD0
	GPHUP	= 0x0c;		// GPH2,GPH#使用内部上拉 

	ULCON0 = 0x03;		// 8N1(8个数据位，无校验，1个停止位)
	UCON0  = 0x05;		// 查询方式，UART时钟源为PCLK
	UFCON0 = 0x00;		// 不使用FIFO
	UMCON0 = 0x00;		// 不使用流控

	UBRDIV0 = 50000000 / (115200 * 16) - 1;		// PCLK/(波特率×16)-1
}

#define TXD0READY	(1<<2)
#define RXD0READY	(1)
void putc_uart(unsigned char c)
{
	while(!(UTRSTAT0 & TXD0READY));

	UTXH0 = c;
}

unsigned char getc_uart()
{
	while(!(UTRSTAT0 & RXD0READY));

 	return URXH0;
}

#define		MAX_SIZE	256
void puts_uart(unsigned char *s)
{
	unsigned int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		putc_uart(s[i]);
		if(s[i] == '\r')
		{
			putc_uart('\n');
			return;
		}
		if(s[i] == '\n')
		{
			putc_uart('\r');
			return;
		}

	}
}

void gets_uart(unsigned char *s)
{
	unsigned int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		s[i] = getc_uart();
		putc_uart(s[i]);

		if(s[i]  == '\r')
		{
			s[i+1] = '\n';
			putc_uart(s[i+1]);
			return;
		}
		if(s[i]  == '\n')
		{
			s[i+1] = '\r';
			putc_uart(s[i+1]);
			return;
		}

		if(s[i] == '\b')
		{
			i--;	//此时i--只是退回到'\b'前
			i--;	//此时的i--才是真正的退回
		}
	}
}
