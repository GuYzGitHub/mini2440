.text
.global _start
_start:

			ldr		sp, =4096
			bl		disable_watch_dog
			bl		init_set		 //初始化设置	

			ldr		sp,	=0x34000000
			ldr		lr, =loop
			ldr		pc, =main		 //main的返回值作为led的输出
loop:
			b		error_led

