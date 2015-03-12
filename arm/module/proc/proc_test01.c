/***********************
 * 创建一个只读的proc文件
 * author: zht
 * date: 2012-10-12
 ***********************/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>

/* proc文件的读函数 */
static int my_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int ret = 0;

	ret = sprintf(page, "Kernel time is %ld\n", jiffies);

	return ret;
}


static int __init my_init(void)
{
	struct proc_dir_entry *file;

	//创建文件/proc/proc_ro
	file = create_proc_entry("proc_ro", /* name */
		0444,	/* mode */
		NULL);	/* parent */
	if (!file) {
		printk("Cannot create /proc/proc_ro\n");
		return -1;
	}

	file->read_proc = my_proc_read;

	return 0;
}

static void __exit my_exit(void)
{
	//删除/proc/proc_ro
	remove_proc_entry("proc_ro", NULL);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

