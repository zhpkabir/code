.section .data
output:
.asciz "The result is : %d \n"
.section .text
.global _start
_start:
nop
call function
pushl $0
call exit
function:
pushl %ebp
movl %esp,%ebp
pushl $10
pushl $output
call printf
#addl $8,%esp #用不用??
movl %ebp,%esp
popl %ebp
ret

