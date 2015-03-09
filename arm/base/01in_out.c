#include <stdio.h>

int main(void)
{
	int out;

	__asm__ __volatile__(
		"mov r0, #10\n"
		"mov %0, r0\n"
		:"=r"(out)
		:
		:"r0"
	);
		
	printf("out = %d\n", out);

	return 0;
}
