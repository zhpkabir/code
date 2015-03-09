#include "common.h"
#include "irq.h"

void delay(int n);
void do_soft(void);

int main(int argc, char *argv[])
{
	int cpsr;
	int count = 10;

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);
	
	printf("Hello ARM! %x\n",cpsr & 0x1f);
	request_irq(26, do_soft);
	enable_irq();
	
	while(count--){
		VIC0SOFTINT |= 1 << 26;
		delay(100);
	}

	return 0;
}

void do_soft(void)
{
	int cpsr;

	printf("In Do_soft Start\n");

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);

	printf("Mode Is %x\n", cpsr & 0x1f);

	printf("In Do_soft End\n");

//	VIC0SOFTINTCLEAR = 1 << 26;//Clear Int
	VIC0SOFTINTCLEAR = VIC0IRQSTATUS;//Clear Int
}

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 10000; j++)
			;
}
