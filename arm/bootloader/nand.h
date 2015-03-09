#ifndef NAND_H
#define NAND_H

#define NAND_BASE 0x70200000
#define NFCONF        (*(volatile unsigned int *)(NAND_BASE + 0x00)) 
#define NFCONT        (*(volatile unsigned int *)(NAND_BASE + 0x04)) 
#define NFCMMD        (*(volatile unsigned int *)(NAND_BASE + 0x08)) 
#define NFADDR        (*(volatile unsigned int *)(NAND_BASE + 0x0c)) 
#define NFDATA        (*(volatile unsigned int *)(NAND_BASE + 0x10)) 
#define NFMECCD0      (*(volatile unsigned int *)(NAND_BASE + 0x14)) 
#define NFMECCD1      (*(volatile unsigned int *)(NAND_BASE + 0x18)) 
#define NFSECCD       (*(volatile unsigned int *)(NAND_BASE + 0x1c)) 
#define NFSBLK        (*(volatile unsigned int *)(NAND_BASE + 0x20)) 
#define NFEBLK        (*(volatile unsigned int *)(NAND_BASE + 0x24)) 
#define NFSTAT        (*(volatile unsigned int *)(NAND_BASE + 0x28)) 
#define NFECCERR0     (*(volatile unsigned int *)(NAND_BASE + 0x2C)) 
#define NFECCERR1     (*(volatile unsigned int *)(NAND_BASE + 0x30)) 
#define NFMECC0       (*(volatile unsigned int *)(NAND_BASE + 0x34)) 
#define NFMECC1       (*(volatile unsigned int *)(NAND_BASE + 0x38)) 
#define NFSECC        (*(volatile unsigned int *)(NAND_BASE + 0x3C)) 
#define NFMLCBITPT    (*(volatile unsigned int *)(NAND_BASE + 0x40)) 
#define NF8ECCERR0    (*(volatile unsigned int *)(NAND_BASE + 0x44)) 
#define NF8ECCERR1    (*(volatile unsigned int *)(NAND_BASE + 0x48)) 
#define NF8ECCERR2    (*(volatile unsigned int *)(NAND_BASE + 0x4C)) 
#define NFM8ECC0      (*(volatile unsigned int *)(NAND_BASE + 0x50)) 
#define NFM8ECC1      (*(volatile unsigned int *)(NAND_BASE + 0x54)) 
#define NFM8ECC2      (*(volatile unsigned int *)(NAND_BASE + 0x58)) 
#define NFM8ECC3      (*(volatile unsigned int *)(NAND_BASE + 0x5C)) 
#define NFMLC8BITPT0  (*(volatile unsigned int *)(NAND_BASE + 0x60)) 
#define NFMLC8BITPT1  (*(volatile unsigned int *)(NAND_BASE + 0x64)) 

#define GPPCON (*(volatile unsigned int *)0x7F008160)
#define GPOCON (*(volatile unsigned int *)0x7F008140)
#define MEM_SYS_CFG     (*(volatile unsigned int *)0x7E00F120)

#endif
