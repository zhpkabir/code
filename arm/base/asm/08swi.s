.align 2
.text
.globl main
main:
	stmfd sp!, {r0-r12, lr}
	mov r0, #1
	ldr r1, =string
	mov r2, #12
	swi 0x900004
	ldmfd sp!, {r0-r12, pc}

string:
	.asciz "Hello,world\n"

