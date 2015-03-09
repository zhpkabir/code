#include <stdio.h>

int main(void)
{
#if 0
	int out;

	__asm__ __volatile__(
		"mov r0, #30\n"
		"mov r1, #50\n"
		//"sub r1, r0\n"
		"sub r1, r1, r0\n"
		"mov %0, r1\n"
		:"=&r"(out)
		:
		:"r0", "r1"
	);
		
	printf("out = %d\n", out);
#endif
	int out;

	__asm__ __volatile__(
		"mov r0, #1\n"
		"mov r1, #0\n"
		"adds r0, #0\n"//Clear C
		"subs r1, r1, r0\n"//Set C
		"mov r0, #20\n"
		"mov r1, #30\n"
		"sbc r1, r1, r0\n"//r1 = r1 - r0 - !C
		"mov %0, r1\n"
		:"=&r"(out)
		:
		:"r0", "r1"
	);

	printf("out = %d\n", out);

	return 0;
}
