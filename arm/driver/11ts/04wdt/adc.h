#ifndef ADC_H
#define ADC_H

#define ADCCON         	(*(volatile unsigned int *)0x7E00B000) 
#define ADCTSC         	(*(volatile unsigned int *)0x7E00B004)
#define ADCDLY         	(*(volatile unsigned int *)0x7E00B008)
#define ADCDAT0        	(*(volatile unsigned int *)0x7E00B00C) 
#define ADCDAT1        	(*(volatile unsigned int *)0x7E00B010) 
#define ADCUPDN        	(*(volatile unsigned int *)0x7E00B014)
#define ADCCLRINT      	(*(volatile unsigned int *)0x7E00B018) 
#define Reserved       	(*(volatile unsigned int *)0x7E00B01C) 
#define ADCCLRINTPNDNUP	(*(volatile unsigned int *)0x7E00B020)

#endif
