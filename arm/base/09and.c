#include <stdio.h>

int main(void)
{
	int and, orr, eor, bic;

	__asm__ __volatile__(
		"mov r0, #5\n"
		"mov r1, #6\n"
		"and r1, r1, r0\n"
		"mov %0, r1\n"
		"orr r1, r1, r0\n"
		"mov %1, r1\n"
		"eor r1, r1, r0\n"
		"mov %2, r1\n"
		"mov r0, #0xff\n"
		"bic r1, r0, #0x2\n"
		"mov %3, r1\n"
		:"=&r"(and), "=&r"(orr), "=&r"(eor), "=&r"(bic)
		:
		:"r0"
	);
		
	printf("and = %d\n", and);
	printf("orr = %d\n", orr);
	printf("eor = %d\n", eor);
	printf("bic = %x\n", bic);

	return 0;
}
