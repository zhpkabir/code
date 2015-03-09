#include "common.h"

void delay(int n);

int main(int argc, char *argv[])
{
	int i = 100;

	led_init();
		
	while(i--){
		led_on(i % 4);
		delay(10);
		led_off(i % 4);
		delay(10);
	}

	return 0;
}

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 10000; j++)
			;
}
