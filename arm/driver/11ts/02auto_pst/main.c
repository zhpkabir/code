#include "common.h"

void delay(int n);

int main(int argc, char *argv[])
{
	int x;
	int y;

	ts_init();
	while(1){
		auto_pst(&x, &y);
		printf("x = %d, y = %d\n", x, y);	
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









