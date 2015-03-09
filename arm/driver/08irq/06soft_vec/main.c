#include "common.h"
#include "irq.h"

void delay(int n);
//void __attribute__((interrupt("IRQ"))) do_soft(void);
void do_soft(void);

int main(int argc, char *argv[])
{
	int cpsr;
	int count = 10;
	
	uart_init();
	request_irq(26, do_soft);
	enable_irq();
	
	while(count--){
		VIC0SOFTINT |= 1 << 26;
		uprintf("xxxxxxxxxxxxxx\n");
		delay(100);
	}

	return 0;
}

void __attribute__((interrupt("IRQ"))) do_soft(void)
{
	clear_int();	
	VIC0SOFTINTCLEAR = VIC0IRQSTATUS;//Clear Int

	uprintf("In Do_soft\n");

}

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 10000; j++)
			;
}
