#include <common.h>
#include <lib.h>

int main(int argc, char *argv[])
{
	char *p = "Hello DDR!\n";//IRAM
	char *q = (void *)0x54000000;//-->DDR

	clock_init();
	ddr_init();
	uart_init();

	memcpy(q, p, 12);

	uprintf(q);

	return 0;
}
