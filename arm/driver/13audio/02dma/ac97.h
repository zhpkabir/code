#ifndef AC97_H
#define AC97_H

#define GPDCON        (*(volatile unsigned int *)0x7F008060) 
#define GPDDAT        (*(volatile unsigned int *)0x7F008064) 
#define GPDPUD        (*(volatile unsigned int *)0x7F008068) 
#define GPDCONSLP     (*(volatile unsigned int *)0x7F00806C) 
#define GPDPUDSLP     (*(volatile unsigned int *)0x7F008070) 
#define AC_GLBCTRL    (*(volatile unsigned int *)0x7F001000) 
#define AC_GLBSTAT    (*(volatile unsigned int *)0x7F001004) 
#define AC_CODEC_CMD  (*(volatile unsigned int *)0x7F001008) 
#define AC_CODEC_STAT (*(volatile unsigned int *)0x7F00100C) 
#define AC_PCMADDR    (*(volatile unsigned int *)0x7F001010) 
#define AC_MICADDR    (*(volatile unsigned int *)0x7F001014) 
#define AC_PCMDATA    (*(volatile unsigned int *)0x7F001018) 
#define AC_MICDATA    (*(volatile unsigned int *)0x7F00101C) 
	
#endif
