#include <stdio.h>

int main(int argc, char *argv[])
{
	int flag = 0;

	__asm__ __volatile__(
		"create_list:\n"
		"sub sp, sp, #24\n"
		"mov r0, sp\n"
		
		"mov r1, #10\n"
		"str r1, [r0]\n"
		"add r1, r0, #8\n"
		"str r1, [r0, #4]\n"

		"mov r1, #20\n"
		"str r1, [r0, #8]\n"
		"add r1, r0, #16\n"
		"str r1, [r0, #12]\n"

		"mov r1, #30\n"
		"str r1, [r0, #16]\n"
		"mov r1, #0\n"
		"str r1, [r0, #20]\n"

		"find_list:\n"
		"mov r2, #50\n"
		"loop:\n"
		"ldr r1, [r0]\n"
		"cmp r1, r2\n"
		"moveq %0, #1\n"
		"beq end\n"
		"ldr r0, [r0, #4]\n"
		"cmp r0, #0\n"
		"moveq %0, #0\n"
		"beq end\n"
		"b loop\n"
		"end:\n"	
		:"=&r"(flag)
		:
		:"r0", "r1", "r2"
	);

	printf("flag = %d\n", flag);
	
	return 0;
}
