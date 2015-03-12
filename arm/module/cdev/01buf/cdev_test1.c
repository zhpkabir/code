/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-02-24 20:35
 * Filename : cdev_test1.c
 * Description : 
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>

dev_t dev_no;

static __init int test_init(void)
{
	int ret;

	dev_no = MKDEV(98, 2);

	ret = register_chrdev_region(dev_no, 1, "cdev_test");
	if(ret < 0){
		printk("register_chrdev_region() error\n");
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
MODULE_AUTHOR("Zhonghuiping");
MODULE_DESCRIPTION("This is a cdev");
MODULE_VERSION("1.0");
