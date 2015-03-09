.align 2
.global main
.text
main:
	stmfd sp!, {r0-r12, lr}

	mov r1, #100
	mov r2, #200
	adds r1, r1, r2
	ldr r0, =string
	bl printf

	mov r1, #1
	mvn r2, #0
	adds r2, r2, r1
	mov r1, #100
	mov r2, #200
	adc r1, r1, r2
	ldr r0, =string
	bl printf

	mvn r1, #0
	ldr r0, =string
	bl printf
	ldmfd sp!, {r0-r12, pc}
string:
	.asciz "sum=%d\n"
.bss
