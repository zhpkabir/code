#ifndef DMA__H_
#define DMA__H_

#define SDMA_SEL (*(volatile unsigned int *)0x7E00F110)
#define DMA1 (*(volatile unsigned int *)0x75100000)



#define DMACConfiguration       (*(volatile unsigned int *) 0x030) 
#define DMACSync                (*(volatile unsigned int *) 0x034)
#define DMACC0SrcAddr           (*(volatile unsigned int *) 0x100)
#define DMACC0DestAddr          (*(volatile unsigned int *) 0x104)
#define DMACC0LLI               (*(volatile unsigned int *) 0x108)
#define DMACC0Control0          (*(volatile unsigned int *) 0x10C)
#define DMACC0Control1          (*(volatile unsigned int *) 0x110)
#define DMACC0Configuration     (*(volatile unsigned int *) 0x114)
#define DMACC0ConfigurationExp  (*(volatile unsigned int *) 0x118)
#define DMACC1SrcAddr           (*(volatile unsigned int *) 0x120)
#define DMACC1DestAddr          (*(volatile unsigned int *) 0x124)
#define DMACC1LLI               (*(volatile unsigned int *) 0x128)
#define DMACC1Control0          (*(volatile unsigned int *) 0x12C)
#define DMACC1Control1          (*(volatile unsigned int *) 0x130)
#define DMACC1Configuration     (*(volatile unsigned int *) 0x134)
#define DMACC1ConfigurationExp  (*(volatile unsigned int *) 0x138)






#endif
