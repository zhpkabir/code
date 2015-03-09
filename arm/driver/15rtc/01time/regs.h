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

#endif
