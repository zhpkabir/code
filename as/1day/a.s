.section .data
str:
	.asciz "Hello,world\n"
.section .text
.global _start
_start:
nop
pushl $str
call printf
add $8,%esp
pushl $0
call exit 
