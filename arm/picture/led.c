#include "common.h"
#include "regs.h"

void led_init(void)
{
	GPMCON &= ~(0xffff);
	GPMCON |= 0x1111;

	GPMDAT |= 0xf;
}

void led_on(int n)
{
	GPMDAT &= ~(1 << n);
}

void led_off(int n)
{
	GPMDAT |= 1 << n;
}
