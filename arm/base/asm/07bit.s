.align 2
.globl main
main:
	stmfd sp!, {r0-r12,lr}

	mov r0, #5
	mov r1, #6
	and r1, r1, r0
	mov r2, r1
	orr r1, r1, r0
	mov r3, r1
	eor r1, r1, r0
	mov r4, r1
	mov r0, #0xff
	bic r1, r0, #0x2
	mov r5, r1

	ldr r0, =string
	mov r1, r2
	mov r2, r3
	mov r3, r4
	sub sp, sp, #4
	str r5, [sp]
	bl printf
	add sp, sp, #4
	
	ldmfd sp!, {r0-r12,pc}
string:
	.asciz "%d,%d,%d,%d\n"
