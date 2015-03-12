/***********************************
 * Use seq_file to implement proc file_operations
 * Author: zht
 * Date: 2011-12-15
 ***********************************/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

struct proc_head {
	struct list_head phead;
	int item_count;
	int str_count;
};

struct proc_item {
	struct list_head pitem;
	char *pbuf;
	int num;
};

struct proc_head *my_head;



/************************
 * seq_operations->start
 ************************/
static void *my_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct proc_item *entry;

        if (*pos == 0)
		seq_printf(seq, "List has %d items, total %d bytes\n", my_head->item_count, my_head->str_count);

	/* get first item */
	++*pos;
	printk("Start:pos=%d\n",*pos);
	list_for_each_entry(entry, &my_head->phead, pitem) {
		if (*pos == entry->num)
		{
	printk("Start:pos=%d\n",*pos);
			return entry;
		}
	}

        return NULL;
}


/************************
 * seq_operations->next
 ************************/
static void *my_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{	
	struct proc_item *entry;
	
	/* get next item */
	++*pos;
	printk("Next:pos=%d\n",*pos);
	list_for_each_entry(entry, &my_head->phead, pitem) {
		if (*pos == entry->num)
		{
	printk("Next:pos=%d\n",*pos);
			return entry;
		}
        }

        return NULL;
}


/************************
 * seq_operations->stop
 ************************/
static void my_seq_stop(struct seq_file *m, void *v)
{}


/************************
 * seq_operations->show
 ************************/
static int my_seq_show(struct seq_file *m, void *v)
{
	struct proc_item *tmp = v;
	printk("Show\n");
	seq_printf(m, "%s", tmp->pbuf);
	return 0;
}


static struct seq_operations my_seq_fops = {
	.start 	= my_seq_start,
	.next 	= my_seq_next,
	.stop	= my_seq_stop,
	.show	= my_seq_show,
};


/*************************
 * file_operations->open
 *************************/
static int proc_seq_open(struct inode *inode, struct file *file)
{
        return seq_open(file, &my_seq_fops);
}


/*************************
 * file_operations->write
 *************************/
ssize_t proc_seq_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct proc_item *tmp;

	//allocate proc_item
	tmp = (struct proc_item *)kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (NULL == tmp)
		return -ENOMEM;
	INIT_LIST_HEAD(&tmp->pitem);

	//alloc new buffer
	tmp->pbuf = (unsigned char *)kzalloc(count, GFP_KERNEL);
	if (NULL == tmp->pbuf) {
		kfree(tmp);
		return -ENOMEM;
	}
	if (copy_from_user(tmp->pbuf, buf, count)) {
		kfree(tmp->pbuf);
		kfree(tmp);
		return -1;
	}
	
	list_add(&tmp->pitem, &my_head->phead);
	my_head->item_count++;
	my_head->str_count += count;
	tmp->num = my_head->item_count;

	return count;
}


static struct file_operations proc_seq_fops = {
        .open    = proc_seq_open,
        .read    = seq_read,
	.write	 = proc_seq_write,
        .llseek  = seq_lseek,
        .release = seq_release,
};


static int __init my_init(void)
{
	struct proc_dir_entry *file;

	/* alloc & init proc_head */
	my_head = (struct proc_head *)kzalloc(sizeof(*my_head), GFP_KERNEL);
	if (NULL == my_head)
		return -ENOMEM;
	my_head->item_count = 0;
	my_head->str_count = 0;
	INIT_LIST_HEAD(&my_head->phead);

	/* create /proc/proc_seq */
	file = proc_create_data("proc_seq", /* name */
			0,		/* mode */
			NULL,		/* parent */
			&proc_seq_fops,	/* file_operations */
			NULL);		/* data */

	if (NULL == file) {
		kfree(my_head);
		printk("Cannot create /proc/proc_seq\n");
		return -1;
	}

	return 0;
}


static void __exit my_exit(void)
{
	struct proc_item *tmp1, *tmp2;

	remove_proc_entry("proc_seq", NULL);	
	list_for_each_entry_safe(tmp1, tmp2, &my_head->phead, pitem) {
		list_del(&tmp1->pitem);
		kfree(tmp1->pbuf);
		kfree(tmp1);
	}
	kfree(my_head);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZHANG");

