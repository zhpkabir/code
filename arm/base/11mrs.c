#include <stdio.h>

int main(void)
{
	int cpsr;

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"orr r0, r0, #0x80\n"
		"orr r0, r0, #0xf0000000\n"
		"msr cpsr, r0\n"
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);
		
	printf("cpsr = %x\n", cpsr);

	return 0;
}
