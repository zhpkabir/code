#include <stdio.h>

int main(void)
{
	int lsl, lsr, asr, asr1, ror;

	__asm__ __volatile__(
		"mov r0, #10\n"
		"mov %0, r0, lsl #1\n"
		"mov %1, r0, lsr #1\n"
		"mov %2, r0, asr #1\n"
		"mov r0, #-10\n"
		"mov %3, r0, asr #1\n"
		"mov r0, #0xff\n"
		"mov %4, r0, ror #4\n"
		:"=&r"(lsl), "=&r"(lsr), "=&r"(asr), "=&r"(asr1), "=&r"(ror)
		:
		:"r0"
	);
		
	printf("lsl = %d\n", lsl);
	printf("lsr = %d\n", lsr);
	printf("asr = %d\n", asr);
	printf("asr1= %d\n", asr1);
	printf("ror = %x\n", ror);

	return 0;
}
