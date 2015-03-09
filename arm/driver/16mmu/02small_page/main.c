#include "common.h"
#include "regs.h"

int main(int argc, char *argv[])
{
	unsigned int ttb_base1 = 0x51000000;
	unsigned int ttb_base2 = 0x52000000;

	unsigned int vir = 0x54000000;
	unsigned int phy = 0x54000000;	

	*(unsigned int *)phy = 123;
#if 1
	ttb_init(ttb_base1);//enable mmu domain cp15---start_addr
	((unsigned int *)ttb_base1)[vir >> 20] = (ttb_base2 & 0xfffffc00) | 1;	
	((unsigned int *)ttb_base2)[(vir >> 12) & 0xff] = (phy & 0xfffff000) | 2;
#endif	
	printf("*vir = %d\n", *(unsigned int *)vir);
	return 0;
}
