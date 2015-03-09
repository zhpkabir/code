.section .data
array:
.int 23,2345,12,5,36,457,453,3252,423,54
ss:
.string "data is"
str:
.string " %d"
aa:
.string "\n"
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
print:
	movl $1,%edi
	pushl $ss
	call printf
end:
	movl array(,%edi,4), %eax
	pushl %eax
	pushl $str
	call printf
	inc %edi
	cmpl $10,%edi
	jne end
	pushl $aa
	call printf
	pushl $0 #一定要有,否则程序不能正常结束
	call exit

