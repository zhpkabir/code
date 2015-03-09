#ifndef COMMON_H
#define COMMON_H

//int (*abc)(const char *, ...) = (qianzhuan)0xc7e11df8;
//abc("adfas%d\n", 20);
#define printf(...) (((int (*)(const char *, ...))0xc7e11d70)(__VA_ARGS__))

#define NULL	(void *)0
#endif
