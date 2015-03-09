#ifndef REGS_H
#define REGS_H
/*****************led********************/
#define GPMCON *(volatile unsigned int *)0x7F008820
#define GPMDAT *(volatile unsigned int *)0x7F008824
#define GPMPUD *(volatile unsigned int *)0x7F008828

#endif
