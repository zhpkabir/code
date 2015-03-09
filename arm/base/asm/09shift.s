.align 2
.global main
.text
main:
	stmfd sp!, {r0-r12, lr}
	ldr r0, =string
	mov r1, #0x100
	bl printf
	ldmfd sp!, {r0-r12, pc}
	@bx r14 == mov pc, lr
string:
	.asciz "value=0x%2x!\n"
.bss
