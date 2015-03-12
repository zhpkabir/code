#include <net/net_namespace.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/proc_fs.h> 
#include <linux/seq_file.h> 

#define PROC_NAME "test_proc"
#define MAX_LINES 10

typedef struct item
{
	unsigned long key;
	unsigned char value;
}user_item;

user_item items[4];

MODULE_AUTHOR("ZHANG JIE£ºiptabler@mail.com");
MODULE_LICENSE("GPL");

static void *my_seq_start(struct seq_file *s, loff_t *pos)
{
	static unsigned long counter = 0;
	printk(KERN_INFO"Invoke start\n");

	if ( *pos == 0 )
	{
		/* yes => return a non null value to begin the sequence */
		return &counter;
	}
	else
	{
		/* no => it's the end of the sequence, return end to stop reading */
		*pos = 0;
		return NULL;
	}
}

static void *my_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	unsigned long *tmp_v = (unsigned long *)v;
	printk("Invoke next\n");
	if (*pos < MAX_LINES) {
		(*tmp_v)++;
		(*pos)++; 
		return tmp_v;
	} 
	else 
	{
		*pos = 0;
		return NULL;
	}
}

static void my_seq_stop(struct seq_file *s, void *v)
{
	printk("Invoke stop\n");
}

static int my_seq_show(struct seq_file *s, void *v)
{
	int i;
	loff_t *spos = (loff_t *) v;
	printk("Invoke show\n");
	for (i = 0; i < 4; i++)
	{
		items[i].key = *spos;
	}
	items[0].value = '0';
	items[1].value = '1';
	items[2].value = '2';
	items[3].value = '3';
	seq_printf(s, "%ld=%c,%ld=%c,%ld=%c,%ld=%c;\n", items[0].key,
			items[0].value, items[1].key, items[1].value, items[2].key,
			items[2].value, items[3].key, items[3].value);
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
	printk(KERN_INFO"Initialze /proc/net/test_proc success!\n");
	return 0;
}

void cleanup_module(void)
{
	remove_proc_entry(PROC_NAME, init_net.proc_net);
	printk(KERN_INFO"Remove /proc/net/test_proc success!\n");
}


