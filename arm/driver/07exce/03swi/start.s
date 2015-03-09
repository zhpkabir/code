.align 2
.global _start
_start:
	b reset@addr = 0
	b unde
	b swi@0x08
	b pre_bot
	b dat_bot
	.word 0x00@ int a = 0x00;
	b irq
	b fiq
reset:
	@mode==svc lr_svc
	stmfd sp!, {r0-r12, lr}
	bl main
	ldmfd sp!, {r0-r12, pc}
unde:
	@mode==unde sp_unde lr_unde
	mov sp, #0x52000000@0x57e00000
	stmfd sp!, {r0-r12, lr}
	bl do_unde
@	ldmfd sp!, {r0-r12, lr}@lr--->main:movxxxxx
@	movs pc, lr
	ldmfd sp!, {r0-r12, pc}^
swi:
	@mode==svc sp_svc lr_svc
	@uboot--->svc--->sp_svc
	stmfd sp!, {r0-r12, lr}
	sub r0, lr, #4
	bl do_swi
@	ldmfd sp!, {r0-r12, lr}
@	movs pc, lr
	ldmfd sp!, {r0-r12, pc}^
pre_bot:
dat_bot:
irq:
fiq:
