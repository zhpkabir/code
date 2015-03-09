#include "nand.h"
#include "common.h"

#define ENABLE_NAND	NFCONT &= ~(1 << 1)
#define DISABLE_NAND	NFCONT |= 1 << 1
#define READY_NAND	while(!(NFSTAT & 1))

void nand_init(void)
{
	//csn2--->nand
	MEM_SYS_CFG &= ~0x3f;
	//gpo2--->csn2
	GPOCON &= ~0x3;
	GPOCON |= 2;
	//gpp3-gpp7--->nand_ctl
	GPPCON &= ~(0x3ff << 6);
	GPPCON |= 0xaa80;

	NFCONF = (0 << 12) | (2 << 8) | (1 << 4) | (1 << 2);	
	NFCONT = (1 << 1) | (1);

	ENABLE_NAND;
	NFCMMD = 0xff;//reset
	READY_NAND;
	DISABLE_NAND;
}

//nand 9
void send_block_addr(unsigned int addr)
{
	unsigned int raw_addr = (addr >> 11) & 0x1ffff;

	NFADDR = raw_addr & 0xff;//11-18
	NFADDR = (raw_addr >> 8) & 0xff;//19-26
	NFADDR = (raw_addr >> 16) & 0x1;//27
}

//nand 9
void send_addr(unsigned int addr)
{
	unsigned int col_addr = addr & 0x7ff;
	unsigned int raw_addr = (addr >> 11) & 0x1ffff;

	NFADDR = col_addr & 0xff;//0-7
	NFADDR = (col_addr >> 8) & 0x7;//8-10

	NFADDR = raw_addr & 0xff;//11-18
	NFADDR = (raw_addr >> 8) & 0xff;//19-26
	NFADDR = (raw_addr >> 16) & 0x1;//27
}

void nand_erase(unsigned int nand, unsigned int len)
{
	unsigned int addr;	

	ENABLE_NAND;
	//clear muti blocks
	for(addr = nand; addr < nand + len; addr += 2048 * 64){
		NFCMMD = 0x60;
		send_block_addr(addr);
		NFCMMD = 0xd0;
		READY_NAND;
	}

	DISABLE_NAND;
}

//nand 17 
void nand_read(unsigned int ddr, unsigned int nand, unsigned int len)
{
	unsigned int addr;
	int i;

	ENABLE_NAND;
	//read muti pages
	for(addr = nand; addr < nand + len; addr += 2048){
		NFCMMD = 0x00;
		send_addr(addr);
		NFCMMD = 0x30;
		READY_NAND;
		//read a page
		for(i = 0; i < 512; i++, ddr += 4){
		 	*(volatile unsigned int *)ddr= NFDATA;
		}
	}
	DISABLE_NAND;
}

void nand_write(unsigned int ddr, unsigned int nand, unsigned int len)
{
	unsigned int addr;
	int i;
	
	ENABLE_NAND;
	//write muti pages
	for(addr = nand; addr < nand + len; addr += 2048){
		NFCMMD = 0x80;
		send_addr(addr);
		//write a page
		for(i = 0; i < 512; i++, ddr += 4){
			NFDATA = *(volatile unsigned int *)ddr;
		}
		NFCMMD = 0x10;
		READY_NAND;
	}

	DISABLE_NAND;	
}

char *nand_id(char buf[])
{
	char *save = buf;
	
	#define ID_DATA (*(volatile char *)0x70200010)

	ENABLE_NAND;
	NFCMMD = 0x90;
	NFADDR = 0x00;
	READY_NAND;
#if 0
	printf("%x\n", ID_DATA);
	printf("%x\n", ID_DATA);
	printf("%x\n", ID_DATA);
	printf("%x\n", ID_DATA);
	printf("%x\n", ID_DATA);
#endif
	int i;
	for(i = 0; i < 5; i++)
		buf[i] = ID_DATA;

	DISABLE_NAND;

	return save;
}
