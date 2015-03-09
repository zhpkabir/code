#include "common.h"

int main(int argc, char *argv[])
{
	int cpsr;

	printf("In Main Start Mode == %x\n",cpsr & 0x1f);

	__asm__ __volatile__(
		".word 0x77777777\n"//1.cpsr-->spsr_unde 2.add-->lr_unde 3.mode-->unde 4.pc--->-0x04
		"mrs r0, cpsr\n"//add--->lr_unde
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);
	
	printf("In Main End Mode == %x\n",cpsr & 0x1f);

	return 0;
}
