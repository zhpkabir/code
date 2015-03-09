#include "common.h"

int main(int argc, char *argv[])
{
	int ret;

	char buf[2048];//eth frame

	eth_init();

	printf("Vendor Id:%x\n", dm9000_read(0x29));
	printf("Vendor Id:%x\n", dm9000_read(0x28));

	printf("Product Id:%x\n", dm9000_read(0x2a));
	printf("Product Id:%x\n", dm9000_read(0x2b));

	printf("Chip Revision:%x\n", dm9000_read(0x2c));
	while(1){
		if(eth_recv(buf) > 0)
			printf(buf + 42);	
	}

	return 0;
}
