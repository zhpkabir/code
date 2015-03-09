#include "common.h"
#include "regs.h"

int main(int argc, char *argv[])
{
printf("xxxxxxxxxxxxxxxxx\n");
	int *phy = (void *)0x51000000;
	*phy = 123;
	unsigned int ttb_base = 0x54000000;
	

	ttb_init(ttb_base);
	int *vir1 = 0x51000000;
	int *vir2 = 0x12300000;
	sec_map(ttb_base, (unsigned int)vir2, (unsigned int)phy);
	printf("*vir1 = %d\n", *vir1);
	printf("*vir2 = %d\n", *vir2);//123
	
	return 0;
}
