
			/********************
			 *		Dog			*
			 *******************/
#include "s3c2440.h"

void disable_watch_dog()
{
	WTCON = 0;
}

			/********************
			 *	    Clock		*
			 *******************/


/* MPLL(FCLK) = (2 * m * Fin)/(p * 2^s)
 * m = MDIV + 8, p = ODIV + 2,s = SDIV
 * 由于Fin = 12MHZ，(p * 2^s) = 12，只需计算2 × MDIV + 8
 */
#define MPLL_200MHz		((0x5c<<12)|(0x01<<4)|(0x02))
#define MPLL_400MHz		((0xc0<<12)|(0x01<<4)|(0x02))

void clock_set(unsigned char clkdivn, unsigned int mpll)
{
	// LOCKTIME = 0x00ffffff; 锁存时间默认最长
	CLKDIVN = clkdivn;	//推荐设置0x03,HDIVN=1,PDIVN=1 MPLL:FCLK=200MHz,HCLK=100MHz,PCLK=50MHz
	asm 
	(
		"mrc	p15, 0, r1, c1, c0, 0\n"		/*读出控制寄存器 */
		"orr	r1, r1, #0xc0000000\n"			/*设置为"asynchronous bus mode"*/
		"mcr	p15, 0, r1, c1, c0, 0\n"		/*写入控制寄存器*/
	);
	if(mpll == 400)
	{
		MPLLCON = MPLL_400MHz;
	}else{
		MPLLCON = MPLL_200MHz;
	}
}
