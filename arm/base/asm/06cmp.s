.align 2
.global main
.text
main:
	stmfd sp!, {r0-r12, lr}
	mov r1, #100
	mov r2, #9
	cmp r1,r2
	movlt r1, r2
	ldr r0, =string
	bl printf
	ldmfd sp!, {r0-r12, pc}
string:
	.asciz "result=%d\n"
.bss
