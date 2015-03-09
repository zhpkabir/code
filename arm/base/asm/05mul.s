.align 2
.global main
.text
main:
	stmfd sp!, {r0-r12, lr}
	mov r2, #8
	mov r3, #9
	mul r1, r2, r3
	ldr r0, =string
	bl printf
	ldmfd sp!, {r0-r12, pc}
string:
	.asciz "result=%d\n"
.bss
