	.section	.rodata
.LC0:
	.string	"hello,world\n"
	.text
.globl _start 
_start:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$12, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	call	write
	movl	$0, %eax
	leave
	ret
