	.cpu arm10tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"03in_out.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"out = %d\012\000"
	.align	2
.LC1:
	.ascii	"in_out = %d\012\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	mov	r3, #100
	str	r3, [fp, #-16]
	mov	r3, #10
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-8]
#APP
mov r0, r3
mov r1, r0
mov r0, r2
mov r3, r0

@ 0 "" 2
	mov	r2, r1
	str	r2, [fp, #-12]
	str	r3, [fp, #-8]
	ldr	r0, .L3
	ldr	r1, [fp, #-12]
	bl	printf
	ldr	r0, .L3+4
	ldr	r1, [fp, #-8]
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L4:
	.align	2
.L3:
	.word	.LC0
	.word	.LC1
	.size	main, .-main
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
