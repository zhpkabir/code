#include <stdio.h>

int main(void)
{
	int out;

	__asm__ __volatile__(
		"mov r0, #2\n"
		"mov r1, #3\n"
		"mul r2, r1, r0\n"
		"mov %0, r2\n"
		:"=&r"(out)
		:
		:"r0"
	);
		
	printf("out = %d\n", out);

	return 0;
}
