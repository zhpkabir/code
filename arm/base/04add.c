#include <stdio.h>

int main(void)
{
#if 0
	int out;

	__asm__ __volatile__(
		"mov r0, #10\n"
		"mov r1, #20\n"
		//"add r1, r0\n"
		"add r1, r1, r0\n"
		"mov %0, r1\n"
		:"=&r"(out)
		:
		:"r0"
	);
		
	printf("out = %d\n", out);
#endif
	int out;

	__asm__ __volatile__(
		"mov r0, #1\n"
		"mvn r1, #0\n"
		"adds r0, r0, #0\n"//Clear C
		"adds r1, r1, r0\n"//Set C
		"mov r0, #20\n"
		"mov r1, #30\n"
		"adc r1, r1, r0\n"//r1 = r1 + r0 + C
		"mov %0, r1\n"
		:"=&r"(out)
		:
		:"r0", "r1"
	);

	printf("out = %d\n", out);

	return 0;
}
