#ifndef REGS_H
#define REGS_H
/*****************led********************/
#define GPMCON *(volatile unsigned int *)0x7F008820
#define GPMDAT *(volatile unsigned int *)0x7F008824
#define GPMPUD *(volatile unsigned int *)0x7F008828
/*****************clock******************/
#define APLL_LOCK     *(volatile unsigned int *)0x7E00F000 
#define MPLL_LOCK     *(volatile unsigned int *)0x7E00F004 
#define EPLL_LOCK     *(volatile unsigned int *)0x7E00F008 
#define APLL_CON      *(volatile unsigned int *)0x7E00F00C 
#define MPLL_CON      *(volatile unsigned int *)0x7E00F010 
#define EPLL_CON0     *(volatile unsigned int *)0x7E00F014 
#define EPLL_CON1     *(volatile unsigned int *)0x7E00F018 
#define CLK_SRC       *(volatile unsigned int *)0x7E00F01C 
#define CLK_DIV0      *(volatile unsigned int *)0x7E00F020 
#define CLK_DIV1      *(volatile unsigned int *)0x7E00F024 
#define CLK_DIV2      *(volatile unsigned int *)0x7E00F028 
#define CLK_OUT       *(volatile unsigned int *)0x7E00F02C 
#define HCLK_GATE     *(volatile unsigned int *)0x7E00F030 
#define PCLK_GATE     *(volatile unsigned int *)0x7E00F034 
#define SCLK_GATE     *(volatile unsigned int *)0x7E00F038 
#define MISC_CON      *(volatile unsigned int *)0x7E00F838
#define OTHERS        *(volatile unsigned int *)0x7E00F900

/**************uart****************/
#define ULCON0   	*(volatile unsigned int *)0x7F005000 
#define UCON0   	*(volatile unsigned int *)0x7F005004 
#define UFCON0   	*(volatile unsigned int *)0x7F005008 
#define UMCON0   	*(volatile unsigned int *)0x7F00500C 
#define UTRSTAT0  	*(volatile unsigned int *)0x7F005010 
#define UERSTAT0  	*(volatile unsigned int *)0x7F005014 
#define UFSTAT0  	*(volatile unsigned int *)0x7F005018 
#define UMSTAT0  	*(volatile unsigned int *)0x7F00501C 
#define UTXH0   	*(volatile unsigned char *)0x7F005020 
#define URXH0   	*(volatile unsigned char *)0x7F005024 
#define UBRDIV0  	*(volatile unsigned int *)0x7F005028 
#define UDIVSLOT0 	*(volatile unsigned int *)0x7F00502C 
#define UINTP0  	*(volatile unsigned int *)0x7F005030 
#define UINTSP0  	*(volatile unsigned int *)0x7F005034 
#define UINTM0  	*(volatile unsigned int *)0x7F005038
#define GPACON *(volatile unsigned int *)0x7F008000

/*****************led********************/
#define GPMCON *(volatile unsigned int *)0x7F008820
#define GPMDAT *(volatile unsigned int *)0x7F008824
#define GPMPUD *(volatile unsigned int *)0x7F008828
/*****************clock******************/
#define APLL_LOCK     *(volatile unsigned int *)0x7E00F000 
#define MPLL_LOCK     *(volatile unsigned int *)0x7E00F004 
#define EPLL_LOCK     *(volatile unsigned int *)0x7E00F008 
#define APLL_CON      *(volatile unsigned int *)0x7E00F00C 
#define MPLL_CON      *(volatile unsigned int *)0x7E00F010 
#define EPLL_CON0     *(volatile unsigned int *)0x7E00F014 
#define EPLL_CON1     *(volatile unsigned int *)0x7E00F018 
#define CLK_SRC       *(volatile unsigned int *)0x7E00F01C 
#define CLK_DIV0      *(volatile unsigned int *)0x7E00F020 
#define CLK_DIV1      *(volatile unsigned int *)0x7E00F024 
#define CLK_DIV2      *(volatile unsigned int *)0x7E00F028 
#define CLK_OUT       *(volatile unsigned int *)0x7E00F02C 
#define HCLK_GATE     *(volatile unsigned int *)0x7E00F030 
#define PCLK_GATE     *(volatile unsigned int *)0x7E00F034 
#define SCLK_GATE     *(volatile unsigned int *)0x7E00F038 
#define MISC_CON      *(volatile unsigned int *)0x7E00F838
#define OTHERS        *(volatile unsigned int *)0x7E00F900

#endif
