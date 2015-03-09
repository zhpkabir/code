#include "common.h"
#include "regs.h"

void do_unde(void)
{
	int cpsr;

	printf("In do_unde Start\n");

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);

	printf("Mode == %x\n", cpsr & 0x1f);

	printf("In do_unde End\n");
}

