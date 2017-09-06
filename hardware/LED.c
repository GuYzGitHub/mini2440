					/****************
					 *		LED		*
					 ***************/
#include "s3c2440.h"

#define GPB5_out (1<<10) //LED1
#define GPB6_out (1<<12) //LED2
#define GPB7_out (1<<14) //LED3
#define GPB8_out (1<<16) //LED4

void led_up(unsigned int n)
{
	GPBCON |= (GPB5_out|GPB6_out|GPB7_out|GPB8_out);

	if(n < 16)
	{
		GPBDAT = (~(n<<5));
	}
	else
	{
		GPBDAT = (~(15<<5));
	}
}

void led_down()
{
	GPBCON |= (GPB5_out|GPB6_out|GPB7_out|GPB8_out);

	GPBDAT |= ((1<<5)|(1<<6)|(1<<7)|(1<<8));
}

void wait(volatile unsigned int t)
{
	for(; t>0; t--);
}

void error_led(unsigned int val)
{
/*************************************************
 *			   关于错误代码：				     *
 *	15：	到达指令最后一条,防止程序越界;		 *
 *	14:		copy_memory 函数错误，数据不一致;    *
 ************************************************/
	for(; ;)
	{
		led_up(val);	
		wait(150000);
		led_down();
		wait(150000);
	}
}
