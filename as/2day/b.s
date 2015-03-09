.section .data
str:
.string "data is %d\n"
data:
.int 1,2,3,4,5,6,7,8,9
.globl _start
_start:
	nop
	movl $8,%edi
loop:
	pushl data(,%edi,4)
	pushl $str
	call printf
	dec %edi
	cmpl $-1,%edi
	jne loop
	pushl $0
	call exit
