/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-02-24 20:36
 * Filename : demon.c
 * Description : autocreate dev node in /dev
 */
#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/cdev.h>  
#include <linux/fs.h>  
#include <linux/sched.h>  
#include <asm/uaccess.h>  
#include <linux/device.h>  


static int chropen;  
struct cdev *chardev;  
struct class *my_class;  
static int len;  
static dev_t dev;  

static char *to;  

#define DP_MAJOR MAJOR(dev)  
#define DP_MINOR MINOR(dev)      

static int char_open(struct inode *inode, struct file *file)  
{  
	if(chropen == 0)  
		chropen++;  
	else{  
		printk(KERN_ALERT"Another process open the char device\n");  
		return -1;  
	}  
	try_module_get(THIS_MODULE);  
	return 0;  
}  

static int char_release(struct inode *inode,struct file *file)  
{  
	chropen--;  
	module_put(THIS_MODULE);  
	return 0;  
}  

static ssize_t char_read(struct file *filp,char __user *buffer,size_t length,loff_t *offset)  
{  
	unsigned long nn;  
	nn = copy_to_user(buffer, to, length);  
	printk("buffer = %s\n", buffer);  
	return length;  
}  

static ssize_t char_write(struct file *filp, const char __user *buffer, size_t length, loff_t *offset)  
{  
	unsigned long n;  
	to = (char *)kmalloc((sizeof(char)) * (length+1), GFP_KERNEL);  
	memset(to, '\0', length+1);  
	n = copy_from_user(to, buffer, length);  
	printk("n = %ld\n", n);  
	printk("to = %s\n", to);  
	return length;  
}  

static const struct file_operations char_ops={  
	.read = char_read,  
	.write = char_write,  
	.open = char_open,  
	.release = char_release,  
};  

static int __init char_init(void)  
{  
	printk(KERN_ALERT"Initing......\n");  

	chardev = cdev_alloc();  

	if(chardev == NULL){  
		return -1;  
	}  
	if(alloc_chrdev_region(&dev, 0, 10, "xmimx")){  
		printk(KERN_ALERT"Register char dev error\n");  
		return -1;  
	}   
	chropen = 0;  
	len = 0;  
	cdev_init(chardev, &char_ops);  
	if(cdev_add(chardev, dev, 1)){  
		printk(KERN_ALERT"Add char dev error!\n");  
	}  

	my_class = class_create(THIS_MODULE, "xmimx_class");  

	if(IS_ERR(my_class)) {  
		printk("Err: failed in creating class.\n");  
		return -1;  
	}  

	device_create(my_class, NULL, dev, NULL, "xmimx");  
	return 0;  
}  

static void __exit module_close(void)  
{  
	len=0;  
	printk(KERN_ALERT"Unloading..........\n");  

	unregister_chrdev_region(MKDEV(DP_MAJOR,DP_MINOR),10);  
	cdev_del(chardev);  
	device_destroy(my_class, dev);  
	class_destroy(my_class);  
}  

module_init(char_init);  
module_exit(module_close); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZhongHuiping");
MODULE_DESCRIPTION("This is a simple cdev driver");
MODULE_VERSION("1.0");
