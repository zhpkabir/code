#include <stdio.h>

int main(void)
{
	int in = 100;
	int out;

	__asm__ __volatile__(
		"mov r0, %1\n"
		"mov %0, r0\n"
		:"=r"(out)
		:"r"(in)
		:"r0"
	);
		
	printf("out = %d\n", out);

	return 0;
}
