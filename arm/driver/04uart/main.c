#include "common.h"

int main(int argc, char *argv[])
{
	char c;
	char buf[1024];

	uart_init();
	uputchar('a');
	c = ugetchar();
	uputchar(c); 
	uputs("Hello uputs ");
	uputs("Hello uputs\n");

	uputs(ugets(buf));
	uprintf("hello printf %c %s %d %x %%\n", 'h', "nihao", 100, 48);
	
	return 0;
}
