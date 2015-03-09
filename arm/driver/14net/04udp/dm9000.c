#include "regs.h"
#include "common.h"
#include "net.h"

void dm9000_write(char reg, char val)
{	
	*(volatile char *)DM9000_ADDR = reg;
	*(volatile char *)DM9000_DATA = val;
}

char dm9000_read(char reg)
{
	*(volatile char *)DM9000_ADDR = reg;
	return *(volatile char *)DM9000_DATA;
}

void eth_init(void)
{
	SROM_BW |= 1 << 4;
	
	dm9000_write(0x1f, 0x00);
	dm9000_write(0x00, 0x01);
	dm9000_write(0x00, 0x00);
	//MAC
	dm9000_write(0xff, 1 << 7 | 3);
	dm9000_write(0x05, 1 << 4 | 1 << 5 | 1);
}

int eth_send(char *buf, unsigned short len)
{
	unsigned int i;

	if(dm9000_read(0xfe) & 0x80)
		return -1;

	*(volatile char *)DM9000_ADDR = 0xf8;

	for(i = 0; i < ((len + 1) >> 1); i++){
		*(volatile unsigned short *)DM9000_DATA = ((volatile unsigned short *)buf)[i];
	}
	
	dm9000_write(0xfd, (len >> 8) & 0xff);
	dm9000_write(0xfc, len & 0xff);

	dm9000_write(0x02, 0x01);
	
	while((dm9000_read(0xfe) & 0x02) == 0){
		if(0){
			printf("time is over..\n");
			return -1;
		}
	}
	
	dm9000_write(0xfe, 0x02);

	return 0;
}

int eth_recv(char *buf)
{
	unsigned short len, status;
	unsigned int i;

	if((dm9000_read(0xfe) & 0x01) == 0)
		return -1;
	if((dm9000_read(0xf0) & 0x3) != 0x01)
		return -1;	
	if((dm9000_read(0xfe) & 0x80))
		return -1;
	
	*(volatile unsigned short *)DM9000_ADDR = 0xf2;

	status = *(volatile unsigned short *)DM9000_DATA;
	len = *(volatile unsigned short *)DM9000_DATA;

	for(i = 0; i < ((len + 1) >> 1); i++){
		((volatile unsigned short *)buf)[i] = *(volatile unsigned short *)DM9000_DATA;
	}

	dm9000_write(0xfe, 0x01);
}	
