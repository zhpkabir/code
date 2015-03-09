#include <stdio.h>

int main(void)
{
	int out;

	__asm__ __volatile__(
		"mov r0, #30\n"
		"mov r1, #31\n"
		"cmp r0, r1\n"
		"movgt %0, #1\n"
		"movlt %0, #2\n"
		"moveq %0, #3\n"
		:"=&r"(out)
		:
		:"r0", "r1"
	);
		
	printf("out = %d\n", out);

	return 0;
}
