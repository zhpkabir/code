#include "dma.h"
#include "common.h"

struct next_work {
	unsigned int saddr;
	unsigned int daddr;
	unsigned int next;
	unsigned int control0;
	unsigned int control1;
}next_lli;

void ac97_dma_init(unsigned int saddr, unsigned int len, unsigned int daddr)
{
	next_lli.saddr = saddr;
	next_lli.daddr = daddr;
	next_lli.next = (unsigned int)&next_lli;
	next_lli.control0 = (1 << 26) | (1 << 25) | (2 << 21) | (2 << 18) | (1 << 15) | (3);
	next_lli.control1 = ((len + 4 - 1) >> 2);
	
	DMACC0LLI = (unsigned int)&next_lli;
	

	SDMA_SEL |= 1 << 22;//dma1

	DMACC0SrcAddr = saddr;
	DMACC0DestAddr = daddr;
	DMACC0Control0 = (1 << 26) | (1 << 25) | (2 << 21) | (2 << 18) | (1 << 15) | (3);
	DMACC0Control1 = ((len + 4 - 1) >> 2);
	DMACC0Configuration = (1 << 11) | (6 << 6) | (1);
} 

void enable_dma(void)
{
	DMACConfiguration = 1;
}


