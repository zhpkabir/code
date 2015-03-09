.section .rodata
output:
.asciz "The number now is:%d\n"
num:
data1:
.int 1,2,3
data2:
.int 4,5,6

.int 12,23,43,35,15
.section .text
.global _start
_start:
	nop
	movl $0,%edi
loop:
	pushl num(,%edi,4)
	pushl $output
	call printf
	addl $8,%esp
	inc %edi
	cmpl $5,%edi
	jne loop
	pushl $0
	call exit

