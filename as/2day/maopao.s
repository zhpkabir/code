.section .data
str:
.string	"%d "
over:
.string "\n"
array:
.int 23,2345,12,5,36,457,453,3252,423,54
.section .text
.global _start
_start:
	nop
	movl $9,%ecx
	movl $9,%ebx
	movl $array,%esi
loop:
	movl (%esi),%eax
	cmpl 4(%esi),%eax
	jl skip
	xchg %eax,4(%esi)
	movl %eax,(%esi)
skip:
	addl $4,%esi
	dec %ebx
	jnz loop
	dec %ecx
	jz print
	movl %ecx,%ebx
	movl $array,%esi
	jmp loop
	movl $1,%edi
print:
end:
	pushl $0
	call exit
