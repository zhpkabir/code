#include <stdio.h>

int main(void)
{
	int a, b, c;

	__asm__ __volatile__(
		"mov r0, #1\n"
		"mov r1, #2\n"
		"mov r2, #3\n"
		"stmfd sp!, {r0-r2}\n"
		"ldmfd sp!, {r5-r7}\n"
		"mov %0, r5\n"
		"mov %1, r6\n"
		"mov %2, r7\n"
		:"=&r"(a), "=&r"(b), "=&r"(c)
		:
		:"r0"
	);
		
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);

	return 0;
}
