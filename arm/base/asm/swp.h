#ifndef __SWP_H__
#define __SWP_H__

.macro print
	
	ldr r3, =data1
	ldr r4, =data2

	ldr r1,[r3]
	ldr r2,[r4]
	ldr r0, =string
	bl printf
.endm
#endif
