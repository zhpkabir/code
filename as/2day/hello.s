.section .data
str:
.string "Hello,world\n"

.globl _start
_start:
movl $str,%eax
movl $0x41,3(%eax)
pushl $str
call printf
call exit
