#include "common.h"
#include "net.h"

char send_buf[2048];
char recv_buf[2048];
char mac_source[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
//00:E0:4C:46:E4:A2
char mac_destation[6] = {0x00, 0xe0, 0x4c, 0x46, 0xe4, 0xa2};
unsigned int ip_source = (192 << 24) | (168 << 16) | (1 << 8) | (20);
unsigned int ip_destation = (192 << 24) | (168 << 16) | (1 << 8) | (10);
unsigned short port_source = 4321;
unsigned short port_destation = 1234;

void delay(int n);

int main(int argc, char *argv[])
{
	eth_init();
#if 1	
	char *buf = "hello dm9000 driver...";

	while(1){
		memcpy(send_buf + 42, buf, strlen(buf) + 1);
		udp_pack(strlen(buf) + 1);
		printf(send_buf + 42);
		printf("\n");
		delay(100);
	}
#endif

	return 0;
}

void delay(int n)
{	
	int i, j;

	for(i = 0; i < n; i++){
		for(j = 0; j < 10000; j++){
			;
		}
	}

}
