#ifndef _LED_H
#define _LED_H

/* 点亮led灯，当n小于16时led表示n的二进制值
 * 大于16时所有灯点亮
 */
void led_up(unsigned int n);

/* 使用循环方式等待 */
void wait(volatile unsigned int t);

/*************************************************
 * 使用led闪烁方式调试程序						 *
 *												 *
 *             关于错误代码：                    *
 *  15：    到达指令最后一条,防止程序越界;       *
 *  14:     copy_memory 函数错误，数据不一致;    *
 ************************************************/
void error_led(unsigned int val);



#endif
