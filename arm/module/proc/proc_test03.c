/***********************
 * 基于list_head实现proc文件
 * author: zht
 * date: 2012-10-12
 ***********************/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h> /* copy_to|from_user */
#include <linux/list.h>

struct proc_head {
	int file_size;
	struct list_head head;
};

struct proc_item {
	char *str;
	struct list_head item;
};

static struct proc_head *filehead;


/* proc文件的读函数 */
static int my_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int ret = 0;
	struct proc_item *tmp;
	struct list_head *pos;

	/* 遍历链表 */
	//list_for_each_prev
	list_for_each(pos, &filehead->head) {
		tmp = container_of(pos, struct proc_item, item);
		ret += sprintf(page+ret, "%s", tmp->str);
	}

	ret += sprintf(page+ret, "File size is %d bytes\n", filehead->file_size);

	return ret;
}

/* proc文件的写函数 */
static int my_proc_write(struct file *filp, const char __user *buf, unsigned long count, void *data)
{
	struct proc_item *tmp;

	tmp = (struct proc_item *)kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	tmp->str = (char *)kzalloc(count, GFP_KERNEL);
	if (!tmp->str) {
		kfree(tmp);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&tmp->item);
	if(copy_from_user(tmp->str, buf, count)) {
		kfree(tmp->str);
		kfree(tmp);
		return -EFAULT;
	}

	list_add_tail(&tmp->item, &filehead->head);
	filehead->file_size += count;

	return count;
}


static int __init my_init(void)
{
	struct proc_dir_entry *file;

	filehead = (struct proc_head *)kzalloc(sizeof(*filehead), GFP_KERNEL);
	if (!filehead)
		return -ENOMEM;

	INIT_LIST_HEAD(&filehead->head);
	filehead->file_size = 0;

	//创建文件/proc/proc_list
	file = create_proc_entry("proc_list", /* name */
		0666,	/* mode */
		NULL);	/* parent */
	if (!file) {
		printk("Cannot create /proc/proc_list\n");
		kfree(filehead);
		return -1;
	}

	file->read_proc = my_proc_read;
	file->write_proc = my_proc_write;

	return 0;
}

static void __exit my_exit(void)
{
	struct proc_item *tmp1, *tmp2;

	/* 删除/proc/proc_list */
	remove_proc_entry("proc_list", NULL);
	list_for_each_entry_safe(tmp1, tmp2, &filehead->head, item) {
		list_del(&tmp1->item);
		kfree(tmp1);
	}
	kfree(filehead);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

