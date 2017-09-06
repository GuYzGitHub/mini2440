#include "s3c2440.h"
#include "LED.h"
#include "clock.h"
#include "SDRAM.h"
#include "UART.h"

void init_set()
{
	clock_set(0x03, 200);	//FCLK:HCLK:PCLK=400:100:50
	sdram_set();
	copy_memory((volatile unsigned long *)0x0,
				(volatile unsigned long *)0x30000000,
				4096);

	uart0_set();
}
