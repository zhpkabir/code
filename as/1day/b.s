.section .data
output:
.asciz "Now my age is %d \n"
age:
.int 23
.section .text
.global _start
_start:
nop
pushl age
pushl $output
call printf
add $8,%esp
pushl $0
call exit
