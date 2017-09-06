#ifndef _SDRAM_H
#define _SDRAM_H

/* 初始化sdram控制器，设置时钟，块设置
 * REFRESH,HCLK=12MHz:  0x008C07A3,
 * HCLK=100MHz: 0x008C04F4
 */
void sdram_set();

/* copy内存数据，
 * SouAddr 源地址，
 * DesAddr 目标地址，
 * size 大小
 * copy结束后检查结果，若失败，error_led(14)
 */
void copy_memory(volatile unsigned long* SouAddr,
				 volatile unsigned long* DesAddr,
			     unsigned int size);



#endif
