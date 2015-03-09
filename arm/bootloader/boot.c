#include "common.h"

void arm_boot(void)
{//0--2000
	clock_init();
	ddr_init();
	nand_init();
	eth_init();
	led_init();

	nand_read(0x57000000, 0, 0x40000);	

	__asm__ __volatile__(
		"mov sp, #0x58000000\n"
		"ldr pc, =main\n"
	);	
}
