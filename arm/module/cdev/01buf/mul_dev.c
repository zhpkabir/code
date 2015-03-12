/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-02-25 15:45
 * Filename : mul_dev.c
 * Description : 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>

#define DEV_NUM   16

int char_open(struct inode *no, struct file *fp)
{
	return 0;
}

int char_release(struct inode *no, struct file *fp)
{
	return 0;
}

struct file_operations char_ops = {
	.open = char_open,
	.release = char_release,
};

struct cdev dev[DEV_NUM];
struct class *cls;
dev_t dev_no;

static __init int my_init(void)
{
	int ret,i;

	ret = alloc_chrdev_region(&dev_no, 0, DEV_NUM, "led");
	if(ret < 0){
		printk("alloc_chrdev_region chrdev_test1 error\n");
		return -EPERM;
	}
	cls = class_create(THIS_MODULE,"led");
	if(!cls)
		goto class_err;
	printk("MAJOR : %d\nMINOR : %d\n", MAJOR(dev_no), MINOR(dev_no));
	for(i=0; i<DEV_NUM; i++){
		cdev_init(&dev[i], &char_ops);
		cdev_add(&dev[i], dev_no+i, 1);
		if(device_create(cls,NULL,dev_no+i,NULL,"led%d",i)<0)goto device_err;
	}
	return 0;

device_err:
	while(i--) {
		device_destroy(cls,dev_no+i);
		cdev_del(&dev[i]);
	}
	class_destroy(cls);
class_err:
	unregister_chrdev_region(dev_no,DEV_NUM);
	return 0;
}

static __exit void my_exit(void)
{
	int i;
	for(i=0;i<DEV_NUM;i++)
	{
		device_destroy(cls,dev_no + i);
		cdev_del(&dev[i]);
	}

	class_destroy(cls);
	unregister_chrdev_region(dev_no, DEV_NUM);

	printk("Byebye module\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZhiYongLi");
MODULE_DESCRIPTION("This is simple test for module");
MODULE_VERSION("1.0");
