#include "common.h"

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 10000; j++)
			;
}
