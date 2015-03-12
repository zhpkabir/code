#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>

static struct delayed_work init_work;
void work_func(struct work_struct *work)
{
	printk("init working\n");
}



int __init init_init(void)
{
	printk("init begin\n");
	INIT_DELAYED_WORK(&init_work, work_func);
	schedule_delayed_work(&init_work, 2 * HZ);
	return 0;
}

void __exit init_exit(void)
{
	printk("init end\n");
}

module_init(init_init);
module_exit(init_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping");
