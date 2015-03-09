#include "common.h"

int main(int argc, char *argv[])
{
	int cpsr;

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);
	
	driver_init();
	ops();
	printf("Hello ARM! %x\n",cpsr & 0x1f);
	

	return 0;
}
