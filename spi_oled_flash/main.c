/* 2017年9月6日，最后调试 
 * spi控制器
 */

#include "UART.h"
#include "oled.h"
int main()
{
	char * str;
	puts_uart("Init Ok!\n\r");
	print_oled(0, 0, "Init Ok!");
	gets_uart(str);
	puts_uart(str);
	
	return 15; //返回值作为led的输出
}
