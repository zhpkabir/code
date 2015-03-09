#include "common.h"

//nand erase xx xx
//go 50000000 erase xx xx
//go 50000000 = ./a.out = argv[0]
//nand read xx xx xx
//go 50000000 read xx xx xx
//nand write xx xx xx
//go 50000000 write xx xx xx

int main(int argc, char *argv[])
{
	char buf[10];
	int i;

	//tftp 54000000 zImage
	//nand erase 40000 300000
	nand_id(buf);
	for(i = 0; i < 5; i++)
		printf("%x\n", buf[i]);
	nand_erase(0x40000, 0x300000);
	//nand write 50000000 40000 300000
	nand_write(0x54000000, 0x40000, 0x300000);
	
	nand_read(0x50008000, 0x40000, 0x300000);
	//bootm 50008000

	return 0;
}
