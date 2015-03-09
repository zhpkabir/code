#include "common.h"
#include "irq.h"

void clear_int(void)
{
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

int request_irq(int n, void (*handle)(void))
{
	if(n >= 0 && n <= 31){
		VIC0INTSELECT &= ~(1 << n);
		VIC0VECTADDR[n] = (unsigned int)handle;
		VIC0INTENABLE = 1 << n;
	}else if(n >= 32 && n <= 63){
		n -= 32;
		VIC1INTSELECT &= ~(1 << n);
		VIC1VECTADDR[n] = (unsigned int)handle;
		VIC1INTENABLE = 1 << n;
	}else{
		return -1;
	}

	return 0;
}

void enable_irq(void)
{
	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"bic r0, r0, #0x80\n"
		"msr cpsr, r0\n"
		:
		:
		:"r0"
	);
}

void disable_irq(void)
{
	__asm__ __volatile__(
		"mrs r0, cpsr\n"
		"orr r0, r0, #0x80\n"
		"msr cpsr, r0\n"
		:
		:
		:"r0"
	);
}

void dm9000_int_init(void (*handle)(void))
{
	//extern 7
	GPNCON &= ~(3 << 14);
	GPNCON |= 2 << 14;

	EINT0CON0 &= ~(7 << 12);
	EINT0CON0 |= 1 << 12;

	EINT0MASK &= ~(1 << 7);

	request_irq(1, handle);
	enable_irq();	
}
