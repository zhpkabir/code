#ifndef LZY_REGS_H
#define LZY_REGS_H

/*********************************RTC***********************************/
#define INTP      (*(volatile unsigned int *)0x7E005030) 
#define RTCCON    (*(volatile unsigned int *)0x7E005040) 
#define TICCNT    (*(volatile unsigned int *)0x7E005044) 
#define RTCALM    (*(volatile unsigned int *)0x7E005050) 
#define ALMSEC    (*(volatile unsigned int *)0x7E005054) 
#define ALMMIN    (*(volatile unsigned int *)0x7E005058) 
#define ALMHOUR   (*(volatile unsigned int *)0x7E00505C) 
#define ALMDATE   (*(volatile unsigned int *)0x7E005060) 
#define ALMMON    (*(volatile unsigned int *)0x7E005064) 
#define ALMYEAR   (*(volatile unsigned int *)0x7E005068) 
#define BCDSEC    (*(volatile unsigned int *)0x7E005070) 
#define BCDMIN    (*(volatile unsigned int *)0x7E005074) 
#define BCDHOUR   (*(volatile unsigned int *)0x7E005078) 
#define BCDDATE   (*(volatile unsigned int *)0x7E00507C) 
#define BCDDAY    (*(volatile unsigned int *)0x7E005080) 
#define BCDMON    (*(volatile unsigned int *)0x7E005084)
#define BCDYEAR   (*(volatile unsigned int *)0x7E005088)
#define CURTICCNT (*(volatile unsigned int *)0x7E005090)
/*********************************IRQ1*************************************/
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
#define VIC1ADDRESS        (*(volatile unsigned int *)(BASE1 + 0xf00))  
/**************************IRQ0********************************************/
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
#define VIC0ADDRESS        (*(volatile unsigned int *)(BASE0 + 0xf00))  

#endif
