.align 2
#include "swp.h"
.global main
.text
main:
	stmfd sp!, {r0-r12,lr}

	print

	ldr r3, =data1
	ldr r4, =data2
	mov r0,r3
	mov r1,r4
	bl myswap

	print 

	ldmfd sp!, {r0-r12,pc}
myswap:
	ldr r2,[r1]
	swp r2,r2,[r0]
	str r2,[r1]
	bx lr
string:
	.asciz "a=%d,b=%d\n"
.data
data1:
	.word 100
data2:
	.word 200

