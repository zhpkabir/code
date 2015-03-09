	b reset@0x50000000
	b unde
	b swi
	b pre_bot
	b dat_bot
	.word 0x00
	ldr pc, _irq@0x50000018
	b fiq
_irq:
	.word irq
reset:
	stmfd sp!, {r0-r12, lr}
	mov r4, #0x50000000
	mov r5, #0
	mov r6, #60
loop:
	ldr r7, [r4], #4
	str r7, [r5], #4
	cmp r5, r6
	blt loop
	bl main
	ldmfd sp!, {r0-r12, pc}
unde:
swi:
pre_bot:
dat_bot:
fiq:
irq:
	mov sp, #0x52000000
	stmfd sp!, {r0-r12, lr}
	bl do_irq
	ldmfd sp!, {r0-r12, lr}
	subs pc, lr, #4
