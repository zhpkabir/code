#ifndef DMA_H
#define DMA_H

#define SDMA_SEL (*(volatile unsigned int *)0x7E00F110)

#define DMA1_BASE 0x75100000
#define DMACSoftBReq           (*(volatile unsigned int *)(DMA1_BASE + 0x020)) 
#define DMACSoftSReq           (*(volatile unsigned int *)(DMA1_BASE + 0x024)) 
#define DMACConfiguration      (*(volatile unsigned int *)(DMA1_BASE + 0x030)) 
#define DMACSync               (*(volatile unsigned int *)(DMA1_BASE + 0x034)) 
#define DMACC0SrcAddr          (*(volatile unsigned int *)(DMA1_BASE + 0x100))
#define DMACC0DestAddr         (*(volatile unsigned int *)(DMA1_BASE + 0x104))
#define DMACC0LLI              (*(volatile unsigned int *)(DMA1_BASE + 0x108))
#define DMACC0Control0         (*(volatile unsigned int *)(DMA1_BASE + 0x10C))
#define DMACC0Control1         (*(volatile unsigned int *)(DMA1_BASE + 0x110))
#define DMACC0Configuration    (*(volatile unsigned int *)(DMA1_BASE + 0x114)) 
#define DMACC0ConfigurationExp (*(volatile unsigned int *)(DMA1_BASE + 0x118)) 

#endif
