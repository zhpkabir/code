#include "common.h"
#include "regs.h"

void button_init(void)
{
	GPNCON &= ~0xfff;
}

