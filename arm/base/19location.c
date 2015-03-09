#include <stdio.h>

int main(void)
{
	__asm__ __volatile__(
		"data:\n"
		".word 0x10, 0x20\n"
		//"ldr r0, data\n"
		"ldr r1, =data\n"
		"ldr r0, [r1]\n"
		:
		:
		:"r0"
	);

	return 0;
}
