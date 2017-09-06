objs := start.o init.o  main.o LED.o UART.o clock.o SDRAM.o  spi.o oled.o

spi.bin: $(objs)
	arm-linux-ld -Tspi.lds -o spi_elf $^
	arm-linux-objcopy -O binary -S spi_elf $@
	arm-linux-objdump -D -m arm spi_elf > spi.dis
	
%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f spi.bin spi_elf spi.dis *.o		
	
