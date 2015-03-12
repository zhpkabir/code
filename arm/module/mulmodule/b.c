#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

extern int printf_m(void);
int  __init print_init(void)
{
	return printf_m();
}


module_init(print_init);
MODULE_AUTHOR("ZHP");
MODULE_LICENSE("GPL");
