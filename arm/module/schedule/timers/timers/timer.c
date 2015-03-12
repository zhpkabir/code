/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-08-26 14:48
 * Filename : timer.c
 * Description : timer sample
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/timer.h>

static struct timer_list timer;

static void timer_func(unsigned long noused)
{
	printk("timer function \n");
	mod_timer(&timer, jiffies + 2*HZ);
}

int __init timer_init(void)
{
	init_timer(&timer);
	timer.function = timer_func;
	timer.expires = jiffies + 2*HZ;
	add_timer(&timer);
	return 0;
}

void __exit timer_exit(void)
{
	del_timer(&timer);
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_AUTHOR("zhonghuiping");
MODULE_LICENSE("GPL");
