.align 2
.global main
.text
main:
	stmfd sp!, {r0-r12, lr}
	ldr r0, =string
	bl printf
	ldmfd sp!, {r0-r12, pc}
	@bx r14 == mov pc, lr
.data
	.word 0x10, 0x20, 0x30
	.short 0x10, 0x20
	.byte 0x10, 0x20
string:
	.asciz "Hello Asm!\n"
.bss
.section .abc
