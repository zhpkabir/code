#include <stdio.h>

int main(void)
{
	int a = 10, b = 11, c = 12;

	__asm__ __volatile__(
		"mov r0, %0\n"
		"mov r1, %1\n"
		"mov r2, %2\n"

		"cmp r0, r1\n"
		"movlt r3, r0\n"
		"movlt r0, r1\n"
		"movlt r1, r3\n"

		"cmp r0, r2\n"
		"movlt r3, r0\n"
		"movlt r0, r2\n"
		"movlt r2, r3\n"
		
		"cmp r1, r2\n"
		"movlt r3, r1\n"
		"movlt r1, r2\n"
		"movlt r2, r3\n"

		"mov %0, r0\n"
		"mov %1, r1\n"
		"mov %2, r2\n"
		:"+r"(a), "+r"(b), "+r"(c)
		:
		:"r0", "r1", "r2"
	);
	
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);

	return 0;
}
