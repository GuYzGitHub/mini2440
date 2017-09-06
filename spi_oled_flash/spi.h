#ifndef _SPI_H
#define _SPI_H

/* 初始化spi控制器 */
void spi_init();

/* 发送一字节数据 */
void spi_send_Byte(unsigned char data);

/* 读取一字节数据 */
unsigned char spi_read_Byte();

#endif
