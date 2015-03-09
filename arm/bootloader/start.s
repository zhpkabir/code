.align 2
.global _start
_start:
	b reset@addr = 0
	b unde
	b swi
	b pre_bot
	b dat_bot
	.word 0x00
	b .@0x18
	b fiq
reset:
	mov r0, #0x70000000
        orr r0, r0, #0x13
        mcr p15, 0, r0, c15, c2, 4

        ldr r0, =0x7e004000
        mov r1, #0
        str r1, [r0]

	@修改中断向量到VIC控制器，即来了中断不再跳往0x18
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #(1 << 24)
	mcr p15, 0, r0, c1, c0, 0
	
	@切换模式来设置中断模式的sp
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0x12
	msr cpsr, r0
	@现在是中断模式
	mov sp, #0x52000000
	@再把模式切换到SVC模式
	mrs r0, cpsr
        bic r0, r0, #0x1f
        orr r0, r0, #0x13
        msr cpsr, r0

	mov sp, #0x2000

	bl arm_boot
	b .
unde:
swi:
pre_bot:
dat_bot:
irq:
fiq:
