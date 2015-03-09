#include "common.h"

void delay(int n);

int main(int argc, char *argv[])
{
	int result;
	int count = 20;

	adc_init();
	while(count--){
		start_adc();
		end_adc();
		Result = return_adc();
		printf("result = %d\n", result);	
		delay(100);
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









