.section .data
output:
.asciz "The max number now is:%d\n"
num:
.int 12,23,35346,43,24250,346
.section .text
.global _start
_start:
	nop
	movl $1,%edi
	movl num,%eax
loop:
	movl num(,%edi,4),%ebx
	cmpl %eax,%ebx
	cmovgl %ebx,%eax
	inc %edi
	cmpl $6,%edi
	jnz loop
	pushl %eax
	pushl $output
	call printf
	addl $8,%esp
	pushl $0
	call exit

