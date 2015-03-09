.text
.align 2
.global	_start 
_start:
	stmfd sp!, {r0-r11, lr}
	bl main
	ldmfd sp!, {r0-r11, pc}
