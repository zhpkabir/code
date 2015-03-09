#include "common.h"
#include "regs.h"

void wdt_init(int ms)
{
	WTCON = (65 << 8) | (1 << 5) | (1 << 3) | (1 << 2);
	WTDAT = 32 * ms;
	WTCNT = 32 * ms;
}
