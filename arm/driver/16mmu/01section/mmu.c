#include "common.h"
#include "regs.h"

void sec_map(unsigned int ttb_base, unsigned int vir, unsigned int phy)
{
	((unsigned int *)ttb_base)[vir >> 20] = (phy & 0xfff00000) | 2;
}

void ttb_init(unsigned int ttb_base)
{
	int vir;
	int phy;

	for(vir = 0; vir < 0x2000; vir += 0x100000){
		phy = vir;
		sec_map(ttb_base, vir, phy);
	}
	for(vir = 0x50000000; vir < 0x58000000; vir += 0x100000){
		phy = vir;
                sec_map(ttb_base, vir, phy);
        }
	for(vir = 0x70000000; vir < 0x80000000; vir += 0x100000){
		phy = vir;
                sec_map(ttb_base, vir, phy);
        }

	__asm__ __volatile__(
		"MCR p15, 0, %0, c2, c0, 0\n"
		"mvn r0, #0\n"
		"MCR p15, 0, r0, c3, c0, 0\n"
		"MRC p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #1\n"
		"MCR p15, 0, r0, c1, c0, 0\n"
		:
		:"r"(ttb_base)
		:"r0"
	);
}
