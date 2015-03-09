.align 2
.global _start
_start:

	@0x70000000
	@256M
	@协处理器c1 c2 c3 .......
	@arm1176手册P342

	mov r0, #0x70000000
	orr r0, r0, #0x13
	mcr p15, 0, r0, c15, c2, 4

	ldr r0, =0x7e004000
	mov r1, #0
	str r1, [r0]

	mov sp, #0x2000
	bl main
@here:
@	b here
	b .
	
