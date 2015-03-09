#include "common.h"
#include "irq.h"

void do_button(void);

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
	
	printf("Hello ARM! %x\n",cpsr & 0x1f);
	extern_int_init(do_button);
	
	return 0;
}

void do_button(void)
{
	int cpsr;

	printf("In Do_button Start\n");
	
	switch(EINT0PEND & 0x3f){
		case 1:
			printf("Button 0 DN.\n");	
			break;
		case 2:
			printf("Button 1 DN.\n");	
			break;
		case 4:
			printf("Button 2 DN.\n");	
			break;
		case 8:
			printf("Button 3 DN.\n");	
			break;
		case 16:
			printf("Button 4 DN.\n");	
			break;
		case 32:
			printf("Button 5 DN.\n");	
			break;
		default:
			break;
	}

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);

	printf("Mode Is %x\n", cpsr & 0x1f);

	printf("In Do_button End\n");
	
	EINT0PEND = EINT0PEND;
}

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 10000; j++)
			;
}
