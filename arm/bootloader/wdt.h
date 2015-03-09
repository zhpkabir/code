#ifndef WDT_H
#define WDT_H

#define WTCON    (*(volatile unsigned int *)0x7E004000) 
#define WTDAT    (*(volatile unsigned int *)0x7E004004) 
#define WTCNT    (*(volatile unsigned int *)0x7E004008) 
#define WTCLRINT (*(volatile unsigned int *)0x7E00400C)

#endif
