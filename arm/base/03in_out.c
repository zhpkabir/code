#include <stdio.h>

int main(void)
{
	int in = 100;
	int out;
	int in_out = 10;

	__asm__ __volatile__(
		/*
		mov r0, r3
		mov r2, r0
		mov r0, r2
		mov r3, r0
		
		&:
 		mov r0, r3
 		mov r1, r0
 		mov r0, r2
 		mov r3, r0
		*/
		"mov r0, %1\n"
		"mov %0, r0\n"
		"mov r0, %2\n"
		"mov %1, r0\n"
		:"=&r"(out), "+r"(in_out)
		:"r"(in)
		:"r0"
	);
		
	printf("out = %d\n", out);
	printf("in_out = %d\n", in_out);

	return 0;
}
