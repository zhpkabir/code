#ifndef LZY_REGS_H
#define LZY_REGS_H

/******************key_led**************************/
#define GPMCON (*(volatile unsigned int *)0x7F008820) 
#define GPMDAT (*(volatile unsigned int *)0x7F008824)
#define GPMPUD (*(volatile unsigned int *)0x7F008828)
#define GPNCON (*(volatile unsigned int *)0x7F008830)
#define GPNDAT (*(volatile unsigned int *)0x7F008834)
#define GPNPUD (*(volatile unsigned int *)0x7F008838)
#define EINT0FLTCON0 (*(volatile unsigned int *)0x7F008910)
/*************************irq 0***********************/
#define BASE0 0x71200000
#define VIC0IRQSTATUS      (*(volatile unsigned int *)(BASE0 + 0x000)) 
#define VIC0FIQSTATUS      (*(volatile unsigned int *)(BASE0 + 0x004))
#define VIC0RAWINTR        (*(volatile unsigned int *)(BASE0 + 0x008))
#define VIC0INTSELECT      (*(volatile unsigned int *)(BASE0 + 0x00C))
#define VIC0INTENABLE      (*(volatile unsigned int *)(BASE0 + 0x010))
#define VIC0INTENCLEAR     (*(volatile unsigned int *)(BASE0 + 0x014))
#define VIC0SOFTINT        (*(volatile unsigned int *)(BASE0 + 0x018))
#define VIC0SOFTINTCLEAR   (*(volatile unsigned int *)(BASE0 + 0x01C))
#define VIC0PROTECTION     (*(volatile unsigned int *)(BASE0 + 0x020))
#define VIC0SWPRIORITYMASK (*(volatile unsigned int *)(BASE0 + 0x024))
#define VIC0PRIORITYDAISY  (*(volatile unsigned int *)(BASE0 + 0x028))
#define VIC0VECTADDR      ((volatile unsigned int *)(BASE0 + 0x100))
#define VIC0VECTADDR0      (*(volatile unsigned int *)(BASE0 + 0x100))
#define VIC0VECTADDR1      (*(volatile unsigned int *)(BASE0 + 0x104))
#define VIC0VECTADDR2      (*(volatile unsigned int *)(BASE0 + 0x108))
#define VIC0VECTADDR3      (*(volatile unsigned int *)(BASE0 + 0x10C))
#define VIC0VECTADDR4      (*(volatile unsigned int *)(BASE0 + 0x110))
#define VIC0VECTADDR5      (*(volatile unsigned int *)(BASE0 + 0x114))
#define VIC0VECTADDR6      (*(volatile unsigned int *)(BASE0 + 0x118))
#define VIC0VECTADDR7      (*(volatile unsigned int *)(BASE0 + 0x11C))
#define VIC0VECTADDR8      (*(volatile unsigned int *)(BASE0 + 0x120))
#define VIC0VECTADDR9      (*(volatile unsigned int *)(BASE0 + 0x124))
#define VIC0VECTADDR10     (*(volatile unsigned int *)(BASE0 + 0x128))
#define VIC0VECTADDR11     (*(volatile unsigned int *)(BASE0 + 0x12C))
#define VIC0VECTADDR12     (*(volatile unsigned int *)(BASE0 + 0x130))
#define VIC0VECTADDR13     (*(volatile unsigned int *)(BASE0 + 0x134))
#define VIC0VECTADDR14     (*(volatile unsigned int *)(BASE0 + 0x138))
#define VIC0VECTADDR15     (*(volatile unsigned int *)(BASE0 + 0x13C))
#define VIC0VECTADDR16     (*(volatile unsigned int *)(BASE0 + 0x140))
#define VIC0VECTADDR17     (*(volatile unsigned int *)(BASE0 + 0x144))
#define VIC0VECTADDR18     (*(volatile unsigned int *)(BASE0 + 0x148))
#define VIC0VECTADDR19     (*(volatile unsigned int *)(BASE0 + 0x14C))
#define VIC0VECTADDR20     (*(volatile unsigned int *)(BASE0 + 0x150))
#define VIC0VECTADDR21     (*(volatile unsigned int *)(BASE0 + 0x154))
#define VIC0VECTADDR22     (*(volatile unsigned int *)(BASE0 + 0x158))
#define VIC0VECTADDR23     (*(volatile unsigned int *)(BASE0 + 0x15C))
#define VIC0VECTADDR24     (*(volatile unsigned int *)(BASE0 + 0x160))
#define VIC0VECTADDR25     (*(volatile unsigned int *)(BASE0 + 0x164))
#define VIC0VECTADDR26     (*(volatile unsigned int *)(BASE0 + 0x168))
#define VIC0VECTADDR27     (*(volatile unsigned int *)(BASE0 + 0x16C))
#define VIC0VECTADDR28     (*(volatile unsigned int *)(BASE0 + 0x170))
#define VIC0VECTADDR29     (*(volatile unsigned int *)(BASE0 + 0x174))
#define VIC0VECTADDR30     (*(volatile unsigned int *)(BASE0 + 0x178))
#define VIC0VECTADDR31     (*(volatile unsigned int *)(BASE0 + 0x17C))
#define VIC0ADDRESS	   (*(volatile unsigned int *)(BASE0 + 0xf00))		
/********************irq 1*******************************************/
#define BASE1 0x71300000
#define VIC1IRQSTATUS      (*(volatile unsigned int *)(BASE1 + 0x000)) 
#define VIC1FIQSTATUS      (*(volatile unsigned int *)(BASE1 + 0x004))
#define VIC1RAWINTR        (*(volatile unsigned int *)(BASE1 + 0x008))
#define VIC1INTSELECT      (*(volatile unsigned int *)(BASE1 + 0x00C))
#define VIC1INTENABLE      (*(volatile unsigned int *)(BASE1 + 0x010))
#define VIC1INTENCLEAR     (*(volatile unsigned int *)(BASE1 + 0x014))
#define VIC1SOFTINT        (*(volatile unsigned int *)(BASE1 + 0x018))
#define VIC1SOFTINTCLEAR   (*(volatile unsigned int *)(BASE1 + 0x01C))
#define VIC1PROTECTION     (*(volatile unsigned int *)(BASE1 + 0x020))
#define VIC1SWPRIORITYMASK (*(volatile unsigned int *)(BASE1 + 0x024))
#define VIC1PRIORITYDAISY  (*(volatile unsigned int *)(BASE1 + 0x028))
#define VIC1VECTADDR      ((volatile unsigned int *)(BASE1 + 0x100))
#define VIC1VECTADDR0      (*(volatile unsigned int *)(BASE1 + 0x100))
#define VIC1VECTADDR1      (*(volatile unsigned int *)(BASE1 + 0x104))
#define VIC1VECTADDR2      (*(volatile unsigned int *)(BASE1 + 0x108))
#define VIC1VECTADDR3      (*(volatile unsigned int *)(BASE1 + 0x10C))
#define VIC1VECTADDR4      (*(volatile unsigned int *)(BASE1 + 0x110))
#define VIC1VECTADDR5      (*(volatile unsigned int *)(BASE1 + 0x114))
#define VIC1VECTADDR6      (*(volatile unsigned int *)(BASE1 + 0x118))
#define VIC1VECTADDR7      (*(volatile unsigned int *)(BASE1 + 0x11C))
#define VIC1VECTADDR8      (*(volatile unsigned int *)(BASE1 + 0x120))
#define VIC1VECTADDR9      (*(volatile unsigned int *)(BASE1 + 0x124))
#define VIC1VECTADDR10     (*(volatile unsigned int *)(BASE1 + 0x128))
#define VIC1VECTADDR11     (*(volatile unsigned int *)(BASE1 + 0x12C))
#define VIC1VECTADDR12     (*(volatile unsigned int *)(BASE1 + 0x130))
#define VIC1VECTADDR13     (*(volatile unsigned int *)(BASE1 + 0x134))
#define VIC1VECTADDR14     (*(volatile unsigned int *)(BASE1 + 0x138))
#define VIC1VECTADDR15     (*(volatile unsigned int *)(BASE1 + 0x13C))
#define VIC1VECTADDR16     (*(volatile unsigned int *)(BASE1 + 0x140))
#define VIC1VECTADDR17     (*(volatile unsigned int *)(BASE1 + 0x144))
#define VIC1VECTADDR18     (*(volatile unsigned int *)(BASE1 + 0x148))
#define VIC1VECTADDR19     (*(volatile unsigned int *)(BASE1 + 0x14C))
#define VIC1VECTADDR20     (*(volatile unsigned int *)(BASE1 + 0x150))
#define VIC1VECTADDR21     (*(volatile unsigned int *)(BASE1 + 0x154))
#define VIC1VECTADDR22     (*(volatile unsigned int *)(BASE1 + 0x158))
#define VIC1VECTADDR23     (*(volatile unsigned int *)(BASE1 + 0x15C))
#define VIC1VECTADDR24     (*(volatile unsigned int *)(BASE1 + 0x160))
#define VIC1VECTADDR25     (*(volatile unsigned int *)(BASE1 + 0x164))
#define VIC1VECTADDR26     (*(volatile unsigned int *)(BASE1 + 0x168))
#define VIC1VECTADDR27     (*(volatile unsigned int *)(BASE1 + 0x16C))
#define VIC1VECTADDR28     (*(volatile unsigned int *)(BASE1 + 0x170))
#define VIC1VECTADDR29     (*(volatile unsigned int *)(BASE1 + 0x174))
#define VIC1VECTADDR30     (*(volatile unsigned int *)(BASE1 + 0x178))
#define VIC1VECTADDR31     (*(volatile unsigned int *)(BASE1 + 0x17C))
#define VIC1ADDRESS        (*(volatile unsigned int *)(BASE1 + 0xf00))     
/*****************************extern interrupt***********************/
#define EINT0CON0 (*(volatile unsigned int *)0x7F008900)
#define EINT0MASK (*(volatile unsigned int *)0x7F008920)
#define EINT0PEND (*(volatile unsigned int *)0x7F008924)
/*****************************uart***********************************/
#define GPACON		(*(volatile unsigned int *)0x7F008000)
#define ULCON0  	(*(volatile unsigned int *)0x7F005000) 
#define UCON0   	(*(volatile unsigned int *)0x7F005004) 
#define UFCON0   	(*(volatile unsigned int *)0x7F005008) 
#define UMCON0   	(*(volatile unsigned int *)0x7F00500C) 
#define UTRSTAT0  	(*(volatile unsigned int *)0x7F005010) 
#define UERSTAT0  	(*(volatile unsigned int *)0x7F005014) 
#define UFSTAT0  	(*(volatile unsigned int *)0x7F005018) 
#define UMSTAT0  	(*(volatile unsigned int *)0x7F00501C) 
#define UTXH0   	(*(volatile unsigned int *)0x7F005020) 
#define URXH0   	(*(volatile unsigned int *)0x7F005024) 
#define UBRDIV0  	(*(volatile unsigned int *)0x7F005028) 
#define UDIVSLOT0 	(*(volatile unsigned int *)0x7F00502C) 
/**************************clock*****************************/
#define APLL_LOCK       (*(volatile unsigned int *)0x7E00F000) 
#define MPLL_LOCK       (*(volatile unsigned int *)0x7E00F004)
#define EPLL_LOCK       (*(volatile unsigned int *)0x7E00F008)
#define APLL_CON        (*(volatile unsigned int *)0x7E00F00C)
#define MPLL_CON        (*(volatile unsigned int *)0x7E00F010)
#define EPLL_CON0       (*(volatile unsigned int *)0x7E00F014)
#define EPLL_CON1       (*(volatile unsigned int *)0x7E00F018)
#define CLK_DIV0        (*(volatile unsigned int *)0x7E00F020)
#define CLK_DIV1        (*(volatile unsigned int *)0x7E00F024)
#define CLK_DIV2        (*(volatile unsigned int *)0x7E00F028)
#define HCLK_GATE       (*(volatile unsigned int *)0x7E00F030)
#define PCLK_GATE       (*(volatile unsigned int *)0x7E00F034)
#define SCLK_GATE       (*(volatile unsigned int *)0x7E00F038)
#define MEM0_CLK_GATE   (*(volatile unsigned int *)0x7E00F03C)
#define MISC_CON        (*(volatile unsigned int *)0x7E00F838)
#define CLK_SRC         (*(volatile unsigned int *)0x7E00F01C)
#define OTHERS          (*(volatile unsigned int *)0x7E00F900)
/******************************ddr***************************/
#define P1_chip_0_cfg 	(*(volatile unsigned int *)0x7E001200)
#define P1MEMCFG3	(*(volatile unsigned int *)0x7E001050)
#define P1MEMSTAT 	(*(volatile unsigned int *)0x7E001000) 
#define P1MEMCCMD 	(*(volatile unsigned int *)0x7E001004)
#define P1DIRECTCMD 	(*(volatile unsigned int *)0x7E001008)
#define P1MEMCFG 	(*(volatile unsigned int *)0x7E00100C)
#define P1REFRESH 	(*(volatile unsigned int *)0x7E001010)
#define P1CASLAT 	(*(volatile unsigned int *)0x7E001014)
#define P1T_DQSS 	(*(volatile unsigned int *)0x7E001018)
#define P1T_MRD 	(*(volatile unsigned int *)0x7E00101C)
#define P1T_RAS 	(*(volatile unsigned int *)0x7E001020)
#define P1T_RC 		(*(volatile unsigned int *)0x7E001024)
#define P1T_RCD 	(*(volatile unsigned int *)0x7E001028)
#define P1T_RFC 	(*(volatile unsigned int *)0x7E00102C)
#define P1T_RP 		(*(volatile unsigned int *)0x7E001030)
#define P1T_RRD 	(*(volatile unsigned int *)0x7E001034)
#define P1T_WR 		(*(volatile unsigned int *)0x7E001038)
#define P1T_WTR 	(*(volatile unsigned int *)0x7E00103C)
#define P1T_XP 		(*(volatile unsigned int *)0x7E001040)
#define P1T_XSR 	(*(volatile unsigned int *)0x7E001044)
#define P1T_ESR 	(*(volatile unsigned int *)0x7E001048)
#define P1MEMCFG2 	(*(volatile unsigned int *)0x7E00104C)
#define MEM_SYS_CFG 	(*(volatile unsigned int *)0x7E00F120)
/*****************************wdt****************************/
#define WTCON    (*(volatile unsigned int *)0x7E004000) 
#define WTDAT    (*(volatile unsigned int *)0x7E004004) 
#define WTCNT    (*(volatile unsigned int *)0x7E004008) 
#define WTCLRINT (*(volatile unsigned int *)0x7E00400C)
/*****************************nand**************************/
#define BASE_NAND 0x70200000
#define NFCONF (*(volatile unsigned int *)(BASE_NAND + 0x00)) 
#define NFCONT (*(volatile unsigned int *)(BASE_NAND + 0x04)) 
#define NFCMMD (*(volatile unsigned int *)(BASE_NAND + 0x08))
#define NFADDR (*(volatile unsigned int *)(BASE_NAND + 0x0c))
#define NFDATA (*(volatile unsigned int *)(BASE_NAND + 0x10))
#define NFSTAT (*(volatile unsigned int *)(BASE_NAND + 0x28))
#define GPOCON (*(volatile unsigned int *)0x7F008140)
#define GPPCON (*(volatile unsigned int *)0x7F008160)
/****************************lcd*****************************/
#define SPCON (*(volatile unsigned int *)0x7F0081A0)
#define MIFPCON (*(volatile unsigned int *)0x7410800C)
#define GPFCON (*(volatile unsigned int *)0x7F0080A0)
#define GPFDAT (*(volatile unsigned int *)0x7F0080A4)
#define GPECON (*(volatile unsigned int *)0x7F008080)
#define GPEDAT (*(volatile unsigned int *)0x7F008084)
#define GPJCON (*(volatile unsigned int *)0x7F008120)
#define GPICON (*(volatile unsigned int *)0x7F008100)
#define VIDCON0  (*(volatile unsigned int *)0x77100000) 
#define VIDCON1  (*(volatile unsigned int *)0x77100004)
#define VIDCON2  (*(volatile unsigned int *)0x77100008)
#define VIDTCON0 (*(volatile unsigned int *)0x77100010)
#define VIDTCON1 (*(volatile unsigned int *)0x77100014)
#define VIDTCON2 (*(volatile unsigned int *)0x77100018)
#define WINCON0  (*(volatile unsigned int *)0x77100020)
#define WINCON1  (*(volatile unsigned int *)0x77100024)
#define WINCON2  (*(volatile unsigned int *)0x77100028)
#define WINCON3  (*(volatile unsigned int *)0x7710002C)
#define WINCON4  (*(volatile unsigned int *)0x77100030)
#define VIDOSD0A (*(volatile unsigned int *)0x77100040)
#define VIDOSD0B (*(volatile unsigned int *)0x77100044)
#define VIDOSD0C (*(volatile unsigned int *)0x77100048)
#define VIDOSD1A (*(volatile unsigned int *)0x77100050)
#define VIDOSD1B (*(volatile unsigned int *)0x77100054)
#define VIDOSD1C (*(volatile unsigned int *)0x77100058)
#define VIDOSD1D       (*(volatile unsigned int *)0x7710005C) 
#define VIDOSD2A       (*(volatile unsigned int *)0x77100060)
#define VIDOSD2B       (*(volatile unsigned int *)0x77100064)
#define VIDOSD2C       (*(volatile unsigned int *)0x77100068)
#define VISOSD2D       (*(volatile unsigned int *)0x7710006C)
#define VIDOSD3A       (*(volatile unsigned int *)0x77100070)
#define VIDOSD3B       (*(volatile unsigned int *)0x77100074)
#define VIDOSD3C       (*(volatile unsigned int *)0x77100078)
#define VIDOSD4A       (*(volatile unsigned int *)0x77100080)
#define VIDOSD4B       (*(volatile unsigned int *)0x77100084)
#define VIDOSD4C       (*(volatile unsigned int *)0x77100088)
#define VIDW00ADD0B0   (*(volatile unsigned int *)0x771000A0)
#define VIDW00ADD0B1   (*(volatile unsigned int *)0x771000A4)
#define VIDW01ADD0B0   (*(volatile unsigned int *)0x771000A8)
#define VIDW01ADD0B1   (*(volatile unsigned int *)0x771000AC)
#define VIDW02ADD0     (*(volatile unsigned int *)0x771000B0)
#define VIDW03ADD0     (*(volatile unsigned int *)0x771000B8)
#define VIDW04ADD0     (*(volatile unsigned int *)0x771000C0)
#define VIDW00ADD1B0   (*(volatile unsigned int *)0x771000D0)
#define VIDW00ADD1B1   (*(volatile unsigned int *)0x771000D4)
#define DW00ADD0B0     (*(volatile unsigned int *)0x771000A0)
#define VIDW00ADD2 (*(volatile unsigned int *)0x77100100)
#define VIDW01ADD2 (*(volatile unsigned int *)0x77100104)
#define VIDW01ADD1B0 (*(volatile unsigned int *)0x771000D8)


/*******************adc**************************************/
#define ADCCON          (*(volatile unsigned int *)0x7E00B000)  
#define ADCTSC          (*(volatile unsigned int *)0x7E00B004) 
#define ADCDLY          (*(volatile unsigned int *)0x7E00B008) 
#define ADCDAT0         (*(volatile unsigned int *)0x7E00B00C) 
#define ADCDAT1         (*(volatile unsigned int *)0x7E00B010) 
#define ADCUPDN         (*(volatile unsigned int *)0x7E00B014)
#define ADCCLRINT       (*(volatile unsigned int *)0x7E00B018)
#define Reserved        (*(volatile unsigned int *)0x7E00B01C) 
#define ADCCLRINTPNDNUP (*(volatile unsigned int *)0x7E00B020)
/*******************************ac97*************************/
#define AC_GLBCTRL 	(*(volatile unsigned int *)0x7F001000) 
#define AC_GLBSTAT 	(*(volatile unsigned int *)0x7F001004)
#define AC_CODEC_CMD 	(*(volatile unsigned int *)0x7F001008)
#define AC_CODEC_STAT 	(*(volatile unsigned int *)0x7F00100C)
#define AC_PCMADDR 	(*(volatile unsigned int *)0x7F001010)
#define AC_MICADDR 	(*(volatile unsigned int *)0x7F001014)
#define AC_PCMDATA 	(*(volatile unsigned int *)0x7F001018)
#define AC_MICDATA 	(*(volatile unsigned int *)0x7F00101C)
#define GPDCON 		(*(volatile unsigned int *)0x7F008060) 
/*******************************dma**************************/
#define DMA1_BASE	0x75100000
#define DMACConfiguration 	(*(volatile unsigned int *)(DMA1_BASE + 0x030)) 
#define DMACC0SrcAddr 		(*(volatile unsigned int *)(DMA1_BASE + 0x100))
#define DMACC0DestAddr 		(*(volatile unsigned int *)(DMA1_BASE + 0x104))
#define DMACC0LLI 		(*(volatile unsigned int *)(DMA1_BASE + 0x108))
#define DMACC0Control0 		(*(volatile unsigned int *)(DMA1_BASE + 0x10C))
#define DMACC0Control1 		(*(volatile unsigned int *)(DMA1_BASE + 0x110))
#define DMACC0Configuration 	(*(volatile unsigned int *)(DMA1_BASE + 0x114))
#define SDMA_SEL		(*(volatile unsigned int *)0x7E00F110) 
/*********************************dm9000*********************/
#define SROM_BW		(*(volatile unsigned int *)0x70000000) 
#define DM9000_ADDR	0x18000000
#define DM9000_DATA	0x18000004



#endif
