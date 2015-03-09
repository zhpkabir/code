#include "common.h"
#include "setup.h"

#define SHELL "[zhangsan@up]# "
char cmd_buf[1024];
void bootm(void);
char *strcpy(char * dest,const char *src);
int strlen(const char * s);

int main(int argc, char *argv[])
{
	uart_init();
//pc > 57000000
	while(1){
		uprintf(SHELL);
		ugets(cmd_buf);
		if(!strcmp(cmd_buf, "bootm")){
			bootm();
		}
		uprintf("\n");	
	}
}

void bootm(void)
{
	nand_read(0x50008000, 0x40000, 0x300000);

	int *tag_list = (void *)0x50000100;
	char *bootargs = "mem=128M root=/dev/nfs nfsroot=192.168.1.253:/nfsroot ip=192.168.1.20 console=ttySAC0,115200";
	void (*kernel)(int zero, int type, int addr) = (void *)0x50008000;

	*tag_list = 2;
	*(tag_list + 1) = ATAG_CORE;

	tag_list += *tag_list;
	*tag_list = ((strlen(bootargs) + 1 + 3) >> 2) + 2;
	*(tag_list + 1) = ATAG_CMDLINE;
	strcpy((void *)(tag_list + 2), bootargs);

	tag_list += *tag_list;
	*tag_list = 0;
	*(tag_list + 1) = ATAG_NONE;

	//irq fiq dma mmu cache 
	//r0-r2  ldr pc, =0x50008000
	kernel(0, 1626, 0x50000100);
}







