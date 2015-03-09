#ifndef COMMON_H
#define COMMON_H

//int (*abc)(const char *, ...) = (qianzhuan)0xc7e11df8;
//abc("adfas%d\n", 20);
#define printf(...) (((int (*)(const char *, ...))0xc7e11d70)(__VA_ARGS__))
#define FRAMEBUFFER	0x55000000
//#define BPP565	1

#endif
