#include "common.h"
#include "net.h"
#include "regs.h"

/*以h开头的变量全部都是主机的信息*/
/*以e开头的变量全部都是开发板的信息*/
//00:E0:4C:46:E4:A2
unsigned char heth[6] = {0x00, 0xe0, 0x4c, 0x46, 0xe4, 0xa2};  //host
unsigned char eeth[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

unsigned int hip = 192 << 24| ( 168 << 16) | (1 << 8) | 10; //192.168.1.10
unsigned int eip = 192 << 24| ( 168 << 16) | (1 << 8) | 20; //192.168.1.20

unsigned short hport;
unsigned short eport;

unsigned char send_buf[2048];
unsigned char recv_buf[2048];

void do_net(void)
{
	unsigned int len;

	if(!(EINT0PEND & (1 << 7))){
		goto end;
	}
	if((len = eth_recv((void *)recv_buf)) > 14){
		eth_unpack();
	}
end:
	EINT0PEND = EINT0PEND;
}


int main(int argc, char *argv[])
{
//tftp 50008000 zImage
//go 50000000 50008000 zImage
//argv[0] = "go 50000000"
//argv[1] = "0x50008000"
//argv[2] = "zImage"
	if(argc != 3){
		printf("%d", argc);
		printf("\nUsage: go 0x50000000 LoadAdress FileName\n\n");
		return -1;
	}

	hport = htons(69);
	eport = htons(4321);
	
	eth_init();

	irq_disable();

	GPNCON &= ~(3 << 14);	
	GPNCON |= 2 << 14;
	EINT0CON0 &= ~(7 << 12);
	EINT0CON0 |= 1 << 12;
	EINT0MASK &= ~(1 << 7);
	
	irq_request(INT_EINT1, do_net);
	
	irq_enable();
#if 0
	struct arphdr{
		xxxx
		dmac = 0xffffffff
		192.168.1.10
		192.168.1.20
		11:22:33:44:55:66
		.......
	}
	int arp_flag = 1;	
	send_buf = [M][ARP]
	send_arp(send_buf, xxx);
	
	while(arp_flag);
#endif				//"50008000" "zImage"
	tftp_down((void *)atoi(argv[1]), argv[2]);

	return 0;
}



