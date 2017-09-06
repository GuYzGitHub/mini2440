/* 2017年9月5日，最后调试 */
#include "UART.h"
int main()
{
	char s[] = "test s[]\n\r";
	
	puts_uart("test\n\r");
	gets_uart(s);
	puts_uart(s);
	return 15; //返回值作为led的输出
}
