#include "common.h"

void delay(int n);
void __attribute__((interrupt("IRQ"))) do_updn(void);
void __attribute__((interrupt("IRQ"))) do_adc(void);

int main(int argc, char *argv[])
{
	int x;
	int y;

	ts_init();
	
	request_irq(62, do_updn);
	request_irq(63, do_adc);
	enable_irq();
	wait_for_dn();
	
	return 0;
}

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 10000; j++)
			;
}









