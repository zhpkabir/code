#include "common.h"

#define SHELL "[zhangsan@uplooking]# "

int main(int argc, char *argv[])
{
	char c;
	char buf[1024];
	
	clock_init();
	uart_init();
#if 0
	uputchar('a');
	c = ugetchar();
	uputchar(c); 
	uputs("Hello uputs ");
	uputs("Hello uputs\n");

	uputs(ugets(buf));
	uprintf("hello printf %c %s %d %x %%\n", 'h', "nihao", 100, 48);
	
#endif
	while(1){
		uprintf(SHELL);
		ugets(buf);
		//
		if(!strcmp(buf, "quzhenzhou")){
			uprintf("xiaopangzi\n");
		}else{
			uprintf("I do not know\n");
		}
		uprintf("\n");
	}
	return 0;
}
