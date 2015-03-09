#include "common.h"
#include "regs.h"


//p == r0--->swi
void do_swi(unsigned int *p)
{
	int cpsr;

	printf("In do_swi Start\n");

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);

	printf("Mode == %x\n", cpsr & 0x1f);
	printf("Swi No Is %d\n", *p & 0xffffff);

	printf("In do_swi End\n");
}

