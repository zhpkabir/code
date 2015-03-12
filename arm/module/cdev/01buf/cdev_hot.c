/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-02-25 11:42
 * Filename : cdev_test4.c
 * Description : 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>

struct buf_st {
	int user;
	dev_t no;
	char buf[1024];
	struct cdev dev;
};

ssize_t cbuf_read(struct file *fp, char __user *buffer, size_t count, loff_t *off)
{
	struct buf_st *bs = fp->private_data;
	int ret = 0;
	printk("Read:%s",bs->buf);
	ret = copy_to_user(buffer, bs->buf, count);

	return count - ret;
}

ssize_t cbuf_write(struct file *fp, const char __user *buffer, size_t count, loff_t *off)
{
	struct buf_st *bs = fp->private_data;
	int ret;
	
	printk("Write:%s",buffer);
	ret = copy_from_user(bs->buf, buffer, count);

	return count - ret;
}

int cbuf_ioctl(struct inode *no, struct file *fp, unsigned int cmd, unsigned long val)
{
	printk("In ioctl.");
	return 0;
}

int cbuf_open(struct inode *no, struct file *fp)
{
	struct buf_st *bs = container_of(no->i_cdev, struct buf_st, dev);
	fp->private_data = (void *)bs;

	bs->user++;
	
	return 0;
}

int cbuf_release(struct inode *no, struct file *fp)
{
	struct buf_st *bs = container_of(no->i_cdev, struct buf_st, dev);

	bs->user--;
	
	return 0;
}

struct file_operations cbuf_ops = {
	.owner = THIS_MODULE,
	.open = cbuf_open,
	.release = cbuf_release,
	.read = cbuf_read,
	.write = cbuf_write,
};

struct buf_st cbuf;

struct class *my_class;
int __init init_module(void)
{
	
	memset(cbuf.buf,'\0',1024);

	cbuf.no=MKDEV(register_chrdev(0,"char1",&cbuf_ops),1);
	if (MAJOR(cbuf.no)<0)
		return -1;

	my_class = class_create(THIS_MODULE,"test");
	if (!my_class)
		goto class_err;

	if(device_create(my_class,NULL,cbuf.no,NULL,"char1")<0)
		goto device_err;

	printk("Create devices:MAJOR:%d, MINOR:%d\n", MAJOR(cbuf.no), MINOR(cbuf.no));
	return 0;

device_err:
	class_destroy(my_class);
class_err:
	unregister_chrdev(MAJOR(cbuf.no),"char1");
	return -1;
}

void __exit cleanup_module(void)
{
	device_destroy(my_class,cbuf.no);
	class_destroy(my_class);
	unregister_chrdev(MAJOR(cbuf.no),"char1");
	printk("Destroy devices:MAJOR:%d, MINOR:%d\n", MAJOR(cbuf.no), MINOR(cbuf.no));
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZhongHuiping");
MODULE_DESCRIPTION("This is a simple hot cdev driver");
MODULE_VERSION("1.0");
