/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-08-26 14:18
 * Filename : hrtimers.c
 * Description : hrtimers sample
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/hrtimer.h>

static struct hrtimer hrt_timer;
static ktime_t ktime;
static int count = 0;
static enum hrtimer_restart hrt_func(struct hrtimer *htimer)
{

	printk("hrtimer functon\n");
	if (count++ != 5)
		return HRTIMER_RESTART;
	else
		return HRTIMER_NORESTART;
}

int __init hrt_init(void)
{ 
	ktime = ktime_set(1,0);
	hrtimer_init(&hrt_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrt_timer.function = hrt_func;
	hrtimer_start(&hrt_timer, ktime, HRTIMER_MODE_REL);
	printk("hrtimer init\n");
	return 0;
}

void __exit hrt_exit(void)
{
	hrtimer_cancel(&hrt_timer);
	printk("hrtimer cancle\n");
}

module_init(hrt_init);
module_exit(hrt_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping");
