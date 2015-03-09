#include "common.h"
#include "regs.h"

void arm_boot(void)
{
	char *ddr_p = (void *)0x57000000;
	WTCON = 0;

	led_init();
	clock_init();
	ddr_init();
	nand_init();

	nand_read(ddr_p, 0, 0x40000);
	led_on(0);

	__asm__ __volatile__(
		"mov sp, #0x58000000\n"		
		"ldr pc, =main\n"
	);
}
