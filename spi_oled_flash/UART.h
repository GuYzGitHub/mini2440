#ifndef _UART_H
#define _UART_H
/* 设置uart时钟等*/
void uart0_set();

/* 输出一个字符 */
void putc_uart(unsigned char c);

/* 输出一个字符串 */
void puts_uart(unsigned char *s);

/* 得到一个字符 */
unsigned char getc_uart();

/* 得到一个字符串 */
void gets_uart(unsigned char *s);
	
		
#endif
