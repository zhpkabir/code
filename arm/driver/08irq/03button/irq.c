#include "common.h"
#include "regs.h"
#include "irq.h"

void do_irq(void)
{
	void (*handle)(void) = NULL;

	if(VIC0ADDRESS){
		handle = (void *)VIC0ADDRESS;
	}else if(VIC1ADDRESS){
		handle = (void *)VIC1ADDRESS;
	}	

	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;

	if(handle){
		handle();
	}
}

//return 0:sucess
//	 -1:faile
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

void extern_int_init(void (*handle)(void))
{
	GPNCON &= ~0xfff;
	GPNCON |= 0xaaa;

	EINT0CON0 &= ~0xfff;
	EINT0CON0 |= 0x222;

	EINT0MASK &= ~0x3f;

	request_irq(0, handle);
	request_irq(1, handle);
	enable_irq();	
}
