#include <stdio.h>

int main(void)
{
#if 0
	int out;

	__asm__ __volatile__(
		"mov %0, #40\n"
		"b end\n"
		"mov %0, #50\n"
		"end:\n"
		:"=&r"(out)
		:
		:"r0"
	);
		
	printf("out = %d\n", out);
#endif

	int out;

	__asm__ __volatile__(
		"mov r0, #1\n"
		"mov r1, #2\n"
		"mov r2, #3\n"
		"mov r3, #4\n"
		"mov r4, #5\n"
		"str r4, [sp, #-4]!\n"
		"mov r4, #6\n"
		"str r4, [sp, #-4]!\n"
		"bl add_test\n"
		"add sp, sp, #8\n"
		"mov %0, r0\n"
		:"=&r"(out)
		:
		:"r0", "r1", "r4"
	);
	
	printf("out = %d\n", out);

	return 0;
}

#if 0
__asm__(
	"add_test:\n"
	"add r0, r0, r1\n"
	"mov pc, r14\n"
);
#endif
int add_test(int a, int b, int c, int d, int e, int f)
{
	return a + b + c + d + e + f;
}
