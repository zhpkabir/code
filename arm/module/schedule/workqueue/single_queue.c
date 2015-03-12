#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>

static struct timer_list timer;
static struct workqueue_struct *work;
static struct work_struct init_work;

void work_func(struct work_struct *work)
{
	printk("queue working\n");
}

void timer_fun(unsigned long noused)
{
	queue_work(work,&init_work);
}

int __init queue_init(void)
{
	init_timer(&timer);
	timer.function = timer_fun;
	timer.expires = jiffies + 2 * HZ;
	add_timer(&timer);
	INIT_WORK(&init_work, work_func);
	work = create_singlethread_workqueue("queue");
	if (work == NULL)
		return -ENOMEM;
	return 0;
}

void __exit queue_exit(void)
{
	del_timer(&timer);
	flush_workqueue(work);
	destroy_workqueue(work);
}

module_init(queue_init);
module_exit(queue_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhonghuiping");
