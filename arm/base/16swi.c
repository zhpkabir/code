#include <stdio.h>

int main(int argc, char *argv[])
{
	char *s = "hello syscall!\n";
	write(1, "hello syscall!\n", 16);
	
	__asm__ __volatile__(
		"mov r0, #1\n"
		"mov r1, %0\n"
		"mov r2, #16\n"
		"swi 0x900004\n"
		:
		:"r"(s)
		:"r0", "r1", "r2"
	);

	return 0;
}
