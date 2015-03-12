/***********************
 * 创建一个可读写的proc文件
 * author: zht
 * date: 2012-10-12
 ***********************/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h> /* copy_to|from_user */

static char *str;

/* proc文件的读函数 */
static int my_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int ret = 0;

	ret = sprintf(page, "%s", str);

	return ret;
}

/* proc文件的写函数 */
static int my_proc_write(struct file *filp, const char __user *buf, unsigned long count, void *data)
{
	char *tmp = kzalloc(count+1, GFP_KERNEL);
	if (!tmp) 
		return -ENOMEM;

	/* copy_from_user(to, from, count) */
	if (copy_from_user(tmp, buf, count)) {
		kfree(tmp);
		return -EFAULT;
	}

	kfree(str);
	str = tmp;

	return count;
}



static int __init my_init(void)
{
	struct proc_dir_entry *file;

	//创建文件/proc/proc_rw
	file = create_proc_entry("proc_rw", /* name */
		0666,	/* mode */
		NULL);	/* parent */
	if (!file) {
		printk("Cannot create /proc/proc_rw\n");
		return -1;
	}

	file->read_proc = my_proc_read;
	file->write_proc = my_proc_write;

	return 0;
}

static void __exit my_exit(void)
{
	//删除/proc/proc_rw
	remove_proc_entry("proc_rw", NULL);
	kfree(str);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

