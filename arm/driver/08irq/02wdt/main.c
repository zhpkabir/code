#include "common.h"

void do_wdt(void);

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
	wdt_init(1000);//unit:ms
	wdt_enable();
	request_irq(26, do_wdt);
	enable_irq();
	
	return 0;
}

void do_wdt(void)
{
	int cpsr;

	printf("In Do_wdt Start\n");

	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"mov %0, r0\n"
		:"=&r"(cpsr)
		:
		:"r0"
	);

	printf("Mode Is %x\n", cpsr & 0x1f);

	printf("In Do_wdt End\n");

	wdt_clr_int();
}
