#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/timer.h>

static struct timer_list timer;
static struct work_struct init_work;
void work_func(struct work_struct *work)
{
	printk("init working\n");
}

void do_func(unsigned long noused)
{
	schedule_work(&init_work);
	mod_timer(&timer, jiffies + 2*HZ);
}


int __init init_init(void)
{
	printk("init begin\n");
	init_timer(&timer);
	timer.function = do_func;
	timer.expires = jiffies + 2*HZ;
	add_timer(&timer);

	INIT_WORK(&init_work, work_func);
	return 0;
}

void __exit init_exit(void)
{
	del_timer(&timer);
	printk("init end\n");
}

module_init(init_init);
module_exit(init_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping");
