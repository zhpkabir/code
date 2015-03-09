#include <stdio.h>

int main()
{
	int out;
	asm(
			"mov r0, #1\n"
			"mov r1, #2\n"
			"mov r2, #3\n"
			"mov r3, #4\n"
			"mov r4, #5\n"
			"str r4, [sp, #-4]!\n"
			"mov r4, #6\n"
			"str r4, [sp, #-4]!\n"
			"bl add_fun\n"
			"add sp, sp, #8\n"
			"mov %[result], r0\n"
			:[result]"=r"(out)
			:
			:"r0", "r1", "r2", "r3", "r4"
	   );
	printf("result is %d \n",out);
	return 0;
}

int add_fun(int a, int b, int c, int d, int e, int f)
{
	return a + b + c + d + e + f;
}
