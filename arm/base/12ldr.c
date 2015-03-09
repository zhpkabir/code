#include <stdio.h>

int main(void)
{
#if 0
	int out;
	int test;

	__asm__ __volatile__(
		"data:\n"
		".word 0x10, 0x20, 0x30\n"
		"ldr r0, data\n" //r0=*data
		"mov %0, r0\n"
		"str r0, %1\n"
		:"=&r"(out)
		:"m"(test)
		:"r0"
	);
		
	printf("out = %d\n", out);
	printf("test = %d\n", test);
#endif
#if 0
	int out, out1, out2;

	__asm__ __volatile__(
		"data:\n"
		".word 0x10, 0x20, 0x30\n"
		"ldr r0, =data\n"
		"ldr %0, [r0]\n"//%0=*r0
//		"add r0, r0, #4\n"
//		"ldr %1, [r0]\n"
//		"ldr %1, [r0, #4]\n"//%1=*(r0 + 4)
//		"ldr %2, [r0, #8]\n"//%2=*(r0 + 8)
		"ldr %1, [r0, #4]!\n"//r0 += 4 %1=*(r0) 
		"ldr %2, [r0, #4]!\n"
		:"=&r"(out), "=&r"(out1), "=&r"(out2)
		:
		:"r0"
	);

	printf("out = %d\n", out);
	printf("out1 = %d\n", out1);
	printf("out2 = %d\n", out2);
#endif
#if 0
	int out, out1, out2;

	__asm__ __volatile__(
		"data:\n"
		".word 0x10, 0x20, 0x30\n"
		"ldr r0, =data\n"
		"ldr %0, [r0], #4\n"//%0=*r0  r0+=4
		"ldr %1, [r0], #4\n"
		"ldr %2, [r0], #4\n"
		:"=&r"(out), "=&r"(out1), "=&r"(out2)
		:
		:"r0"
	);

	printf("out = %d\n", out);
	printf("out1 = %d\n", out1);
	printf("out2 = %d\n", out2);
#endif
	int arr[5];
	int *p = arr;

	__asm__ __volatile__(
		"mov r0, #1\n"		
		"str r0, [%0], #4\n"
		"mov r0, #2\n"
		"str r0, [%0], #4\n"
		"mov r0, #3\n"
		"str r0, [%0], #4\n"
		"mov r0, #4\n"
		"str r0, [%0], #4\n"
		"mov r0, #5\n"
		"str r0, [%0], #4\n"
		:"+r"(p)
		:
		:"r0"
	);	

	int i;
	for(i = 0; i < 5; i++){
		printf("arr[%d] = %d\n", i, arr[i]);
	}

	return 0;
}
