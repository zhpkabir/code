.align 2
.text
.global _start
_start:
	b reset
	b unde
	b swi
	b pre_bot
	b dat_bot
	.word 0x00
	b .
	b fiq
reset:	
	mov r4, #0x70000000
	orr r4, r4, #0x13
	mcr p15, 0, r4, c15, c2, 4

	mrc p15, 0, r4, c1, c0, 0
	orr r4, r4, #(1 << 24)
	mcr p15, 0, r4, c1, c0, 0

	mrs r4, cpsr
	bic r4, r4, #0x1f
	orr r4, r4, #0x12
	msr cpsr, r4
	mov sp, #0x51000000

	mrs r4, cpsr
	bic r4, r4, #0x1f
	orr r4, r4, #0x13
	msr cpsr, r4

	mov sp, #0x2000
	bl arm_boot
	b .
unde:
swi:
pre_bot:
dat_bot:
irq:
fiq:

