#ifndef REGS_H
#define REGS_H
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

#endif
