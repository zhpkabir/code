.section .data
str:
	.string "Your Age is 23\n"
.section .text
.globl _start
_start:
	movl $4,%eax
	movl $1,%ebx
	movl $str,%ecx
	movl $17,%edx
	int $0x80
	mov $1,%eax
	mov $0,%ebx
	int $0x80
