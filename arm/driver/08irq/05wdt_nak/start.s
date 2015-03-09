.align 2
.global _start
_start:
	b reset@addr = 0
	b unde
	b swi
	b pre_bot
	b dat_bot
	.word 0x00
	b irq@0x18
	b fiq
reset:
        mov r0, #0x70000000
        orr r0, r0, #0x13
        mcr p15, 0, r0, c15, c2, 4

        ldr r0, =0x7e004000
        mov r1, #0
        str r1, [r0]

        mov sp, #0x2000
	bl main
	b .
unde:
swi:
pre_bot:
dat_bot:
irq:
	@mode--->irq sp_irq
	mov sp, #0x52000000
@	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}
	bl do_irq
@	ldmfd sp!, {r0-r12, pc}^
	ldmfd sp!, {r0-r12, lr}
	subs pc, lr, #4
fiq:
