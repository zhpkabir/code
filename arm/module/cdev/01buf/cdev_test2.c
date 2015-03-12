/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-02-24 20:35
 * Filename : cdev_test2.c
 * Description : 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

dev_t dev_no;

static __init int test_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev_no, 2, 1, "cdev_test2");	
	if(ret < 0){
		printk("alloc_chrdev_region() error\n");
		return -EPERM;
	}

	printk("MAJOR:%d, MINOR:%d\n", MAJOR(dev_no), MINOR(dev_no));

	return 0;
}

static __exit void test_exit(void)
{
	unregister_chrdev_region(dev_no, 1);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZhongHuiping");
MODULE_DESCRIPTION("This is cdev");
MODULE_VERSION("1.0");
