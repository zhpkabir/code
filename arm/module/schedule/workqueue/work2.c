#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/timer.h>
static struct timer_list timer;
static void work_func(struct work_struct *work)
{
	printk("work begin!\n");
}
//static DECLARE_WORK(work1, work_func);
#include <asm/atomic.h>
struct work_struct work1 = {
	.data = ATOMIC_INIT(0),
	.entry = {&work1.entry, &work1.entry},
	.func = work_func,
};

void do_func(unsigned long noused)
{
	schedule_work(&work1);
	mod_timer(&timer, jiffies + 2*HZ);
}

int __init work_init(void)
{
	init_timer(&timer);
	timer.function = do_func;
	timer.expires = jiffies + 2*HZ;
	add_timer(&timer);
	return 0;
}

void __exit work_exit(void)
{
	del_timer(&timer);
}

module_init(work_init);
module_exit(work_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping");
