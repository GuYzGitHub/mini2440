#ifndef _CLOCK_H
#define	_CLOCK_H
/* 使看门狗无效 */
void disavle_watch_dog();

/*  MPLL(FCLK) = (2 * m * Fin)/(p * 2^s)
 *  m = MDIV + 8, p = ODIV + 2,s = SDIV
 *  由于Fin = 12MHZ，(p * 2^s) = 12，只需计算2 × MDIV + 8
 *  当clkdivn = 0x03 , mpll = 400时  FCLK:HCLK:PCLK=400:100:50
 *    clkdivn = 0x05 , mpll = 400	 FCLK:HCLK:PCLK=400:200:100
 * mpll可选200或400
 */ 
void clock_set(unsigned char clkdivn, unsigned int mpll);

#endif
