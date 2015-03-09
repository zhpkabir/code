#include "common.h"
#include "irq.h"

void __attribute__((interrupt("IRQ"))) do_net(void)
{
	char buf[2048];//eth frame

	if(eth_recv(buf) > 0)
		printf(buf + 42);	
	
	clear_int();
	EINT0PEND = EINT0PEND;
}

int main(int argc, char *argv[])
{
	eth_init();
#if 0
	while(1){
		if(eth_recv(buf) > 0)
			printf(buf + 42);	
	}
#endif
	//1.schedma ----> extern-x gpio
	//2.gpio --->irq ---->high level
	//3.request_irq
	dm9000_int_init(do_net);//extern---x request_irq(x, do_net)
	return 0;
}
