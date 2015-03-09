.section .data
str:
	.ascii "Hello,world\n"
.section .text
.global _start
_start:
nop
pushl $str
call printf
pushl $0
call exit 
