#include <stdio.h>

int main(void)
{
	__asm__ __volatile__(
		"mov r0, #0x20\n"
		"mov r5, #0xff00\n"
		"orr r1, r2, r3\n"
		:
		:
		:"r0"
	);

	return 0;
}
