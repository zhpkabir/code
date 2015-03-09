.section .data
str:
.string "value is %d\n"
.section .text
.global _start
_start:
nop
movl $98,%eax
movl $99,%ebx
movl $1111,%ecx
cmpl %eax,%ebx
cmovcl %eax,%ecx
pushl %ecx
pushl $str
call printf
pushl $0
call exit
