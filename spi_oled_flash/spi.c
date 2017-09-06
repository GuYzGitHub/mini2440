#include "s3c2440.h"

void spi_WaitRedy()
{
	#define REDY	(SPSTA0 & 1)
	for(;!REDY;);
}
			/* 初始化spi控制器 */
void spi_init()
{
	/* GPIO 控制寄存器初始化 
	 * GPG1 OLED_CSn output 
	 * GPG10 FLASH_CSn output
	 */

    GPGCON &= ~((3<<(1*2)) | (3<<(10*2)));
    GPGCON |= (1<<(1*2)) | (1<<(10*2));
    GPGDAT |= (1<<1) | (1<<10);

/*	GPF3  OLED_DC   output
    * GPE11 SPIMISO   
	* GPE12 SPIMOSI   
	* GPE13 SPICLK    
	*/

	GPFCON &= ~(3<<(3*2));    
	GPFCON |= (1<<(3*2));    
    GPECON &= ~((3<<(11*2)) | (3<<(12*2)) | (3<<(13*2)));
    GPECON |= ((2<<(11*2)) | (2<<(12*2)) | (2<<(13*2)));
	

	#define VAL	 (unsigned char)2
	/* 波特率 = PCLK / 2 / (预分频值 + 1) 
	 * PCLK = 50MHz
	 * OLED = 10MHz
	 * FLASH = 104MHz
	 * 最终波特率 = 8.3Mhz
	 */
	SPPRE0 = VAL;	//设置波特率,spi时钟必须低于25MHz

	#define SMOD	(~(3<<5))
	/* SMOD :  SPI 模式选择,决定如何读/写 SPTDAT
	 * 00  :  查询模式
	 * 01  ： 中断模式
	 * 10  :  MDA模式
	 * 11  ： 保留 */
	SPCON0 &= SMOD;				//设置为查询模式
	SPCON0 |= (1<<4)|(1<<3);	//SCK使能,主控模式
	SPCON0 &= ~((1<<2|1<<1)|(1<<0));
}

/* 发送一字节数据 */
void spi_send_Byte(unsigned char data)
{
	spi_WaitRedy();
	SPTDAT0 = data;
}

/* 读取一字节数据 */
unsigned char spi_read_Byte()
{
	SPTDAT0 = 0xff;
	spi_WaitRedy();
	return	SPRDAT0;
}
