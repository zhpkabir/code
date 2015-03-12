/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-08-26 14:19
 * Filename : hrtimer_work.c
 * Description : hrtimer and workwueue sample
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/hrtimer.h>
#include <linux/workqueue.h>

static struct hrtimer hrt_timer;
static struct work_struct hrt_work;  
static ktime_t ktime;

static void work_func(struct work_struct *work)
{
	printk("work addr is %p\n",work);
}

static enum hrtimer_restart hrt_func(struct hrtimer *htimer)
{
	printk("hrtimer functon\n");
	hrtimer_start(&hrt_timer, ktime, HRTIMER_MODE_REL);
	schedule_work(&hrt_work);
	return HRTIMER_NORESTART;
}

int __init hrt_init(void)
{ 
	ktime = ktime_set(5,0);
	hrtimer_init(&hrt_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrt_timer.function = hrt_func;
	hrtimer_start(&hrt_timer, ktime, HRTIMER_MODE_REL);
	printk("hrtimer init\n");
	INIT_WORK(&hrt_work, work_func);
	printk("work init is %p\n",&hrt_work);
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
