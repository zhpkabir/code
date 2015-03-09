#include "dm9000.h"
#include "common.h"

void dm9000_write(char index, char data)
{	
	//send index 0x18000000
	*(volatile unsigned char *)DM9000_INDEX = index;
	//send data 0x18000004
	*(volatile unsigned char *)DM9000_DATA = data;
}

char dm9000_read(char index)
{
	//send index 0x18000000
        *(volatile unsigned char *)DM9000_INDEX = index;
        //read data 0x18000004
        return *(volatile unsigned char *)DM9000_DATA;	
}

void eth_init(void)
{
	SROM_BW |= 1 << 4;//sromc 16
	//power on phy
	dm9000_write(0x1f, 0x00);
	//software reset
	dm9000_write(0x00, 0x01);
	//clear reset && normal mode
	dm9000_write(0x00, 0x00);
	//pointer look-back && enable int for tx rc
	dm9000_write(0xff, (1 << 7) | (0x03));
	//set MAC addr
	dm9000_write(0x10, 0x11);
	dm9000_write(0x11, 0x22);
	dm9000_write(0x12, 0x33);
	dm9000_write(0x13, 0x44);
	dm9000_write(0x14, 0x55);
	dm9000_write(0x15, 0x66);
	//0xff muti addr
	//clear recv send status
	dm9000_write(0xfe, 0x03);
	//clear 
	dm9000_write(0x01, (1 << 2) | (1 << 3) | (1 << 5));
	//enable rc && Discard Long and CRC error Packet
	dm9000_write(0x05, (1 << 5) | (1 << 4) | (1));
}

//return:lenth 
//buf:data
int eth_recv(char *buf)
{
	unsigned short status;
	unsigned short lenth;
	int i;

	//check 
	if(!(dm9000_read(0xfe) & 0x01))
		return -1;

	dm9000_read(0xf0);

	if((dm9000_read(0xf0) & 0x03) != 0x01)
		return -1;
	//16 mode	
	if(dm9000_read(0xfe) & 0x80)
		return -1;	

	*((volatile char *)DM9000_INDEX) = 0xf2;
	status = *(volatile unsigned short *)DM9000_DATA;
	lenth = *(volatile unsigned short *)DM9000_DATA;
	for(i = 0; i < ((lenth + 1) >> 1); i++)
		((volatile unsigned short *)buf)[i] = *(volatile unsigned short *)DM9000_DATA;
	//clear
	dm9000_write(0xfe, 0x01);

	return lenth;
}

int eth_send(char *buf, unsigned short len)
{
	//errror return -1;
	//16 mode       
	int i;

        if(dm9000_read(0xfe) & 0x80)
                return -1;
	
	*(volatile char *)DM9000_INDEX = 0xf8;
	
	for(i = 0; i < ((len + 1) >> 1); i++)
		*(volatile unsigned short *)DM9000_DATA = ((volatile unsigned short *)buf)[i];

	dm9000_write(0xfd, (len >> 8) & 0xff);
	dm9000_write(0xfc, len & 0xff);
	
	dm9000_write(0x02, 0x01);//start send

	while(!(dm9000_read(0xfe) & 0x02));
		//timeout
	
	dm9000_write(0xfe, 0x02);

	return 0;
}
