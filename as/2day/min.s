.section .data
output:
.string "The min value is %d\n"
num:
.int 54,47,67,38,1,36
.section .text
.global _start
_start:
	movl $1,%edi
	movl num,%eax
loop:
	movl num(,%edi,4),%ebx
	cmpl %eax,%ebx
	cmovll %ebx,%eax
	inc %edi
	cmpl $5,%edi
	jnz loop
	pushl %eax
	pushl $output
	call printf
	call exit

