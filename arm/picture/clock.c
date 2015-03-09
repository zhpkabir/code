#include "common.h"
#include "regs.h"

void clock_init(void)
{
	APLL_LOCK = 0xffff;

	APLL_CON = (1 << 31) | (266 << 16) | (3 << 8) | (1);
	OTHERS |= 1 << 6;
	MISC_CON &= ~(1 << 19);
	CLK_DIV0 = (1 << 9) | (1 << 8) | (3 << 12) | (0);
	HCLK_GATE = ~0;
	PCLK_GATE = ~0;

	CLK_SRC |= 1;
}
