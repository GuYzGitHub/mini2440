#ifndef _OLED_H
#define _OLED_H
/* oled初始化 */
void oled_init();

/* 在oled屏幕上打印 
 * page : 一个8×16 bit字符,一个page 8bit,一个字符两个page
 * col  : 列，一个字符8个col
 */
void print_oled(int page, int col, unsigned char *str);
     
#endif
