#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>

static void work_func(struct work_struct *work)
{
	printk("work working!\n");
}
static DECLARE_DELAYED_WORK(work3, work_func);
int __init work_init(void)
{
	printk("work begin!\n");
	schedule_delayed_work(&work3, 3 * HZ);
	return 0;
}

void __exit work_exit(void)
{
	printk("work end!\n");
}

module_init(work_init);
module_exit(work_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping");
