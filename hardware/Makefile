objs := start.o init.o  main.o LED.o UART.o clock.o SDRAM.o

test.bin: $(objs)
	arm-linux-ld -Ttest.lds -o test_elf $^
	arm-linux-objcopy -O binary -S test_elf $@
	arm-linux-objdump -D -m arm test_elf > test.dis
	
%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f test.bin test_elf test.dis *.o		
	
