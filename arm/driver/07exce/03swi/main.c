#include "common.h"

//mode--->svc
int main(int argc, char *argv[])
{
	int cpsr;

	printf("In Main Start Mode == %x\n",cpsr & 0x1f);

	__asm__ __volatile__(
		"swi 50\n"//1.addr--->lr_svc 
			//2.cpsr--->spsr_svc
			//3.mode--->svc
			//4.pc--->0x08
		"mrs r0, cpsr\n"//add--->lr_unde
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);
	
	printf("In Main End Mode == %x\n",cpsr & 0x1f);

	return 0;
}
