#include <net/net_namespace.h> /* for use of init_net*/
#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <linux/proc_fs.h> /* Necessary because we use proc fs */
#include <linux/seq_file.h> /* for seq_file */
#define PROC_NAME "my_seq_proc"

MODULE_AUTHOR("Dreamice dreamice.jiang@mail.com ");
MODULE_LICENSE("GPL");

static void *my_seq_start(struct seq_file *s, loff_t *pos)
{
	static unsigned long counter = 0;
	printk(KERN_INFO"Invoke start\n");
	/* beginning a new sequence ? */
	if ( *pos == 0 )
	{
		/* yes => return a non null value to begin the sequence */
		printk(KERN_INFO"pos == 0\n");
		return &counter;
	}
	else
	{
		/* no => it's the end of the sequence, return end to stop reading */
		*pos = 0;
		printk(KERN_INFO"pos != 0\n");
		return NULL;
	}
}
static void *my_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	unsigned long *tmp_v = (unsigned long *)v;
	printk(KERN_INFO"Invoke next\n");
	(*tmp_v)++;
	(*pos)++;
	return NULL;
}
static void my_seq_stop(struct seq_file *s, void *v)
{
	printk(KERN_INFO"Invoke stop\n");
	/* nothing to do, we use a static value in start() */
}
static int my_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos = (loff_t *) v;
	printk(KERN_INFO"Invoke show\n");
	seq_printf(s, "%Ld\n", *spos);
	return 0;
}
static struct seq_operations my_seq_ops = {
	.start = my_seq_start,
	.next = my_seq_next,
	.stop = my_seq_stop,
	.show = my_seq_show
};
static int my_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &my_seq_ops);
};
static struct file_operations my_file_ops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release
};
int init_module(void)
{
	struct proc_dir_entry *entry;
	entry = create_proc_entry(PROC_NAME, 0, init_net.proc_net);
	if (entry) {
		entry->proc_fops = &my_file_ops;
	}
	printk(KERN_INFO"Initialze my_seq_proc success!\n");
	return 0;
}
/**
 * This function is called when the module is unloaded.
 *
 */
void cleanup_module(void)
{
	remove_proc_entry(PROC_NAME, init_net.proc_net);
	printk(KERN_INFO"Remove my_seq_proc success!\n");
}

