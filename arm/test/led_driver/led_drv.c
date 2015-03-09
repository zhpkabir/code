#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/proc_fs.h>
#include "s3c_led.h"

void led_hrd_init(struct led_info_st *led)
{
	u32 con;
	u32 dat;

	con = readl(led->led_virt + LED_CON);
	con &= GPM_LED_MASK;
	con |= GPM_LED_OUT;
	writel(con, led->led_virt + LED_CON);

	dat = readl(led->led_virt + LED_DAT);	
	dat |= GPM_LED_ALL_OFF;
	writel(dat, led->led_virt + LED_DAT);
}

void led_hrd_exit(struct led_info_st *led)
{
	u32 dat;

	dat = readl(led->led_virt + LED_DAT);	
	dat |= GPM_LED_ALL_OFF;
	writel(dat, led->led_virt + LED_DAT);
}

void led_on(struct led_info_st *led)
{
	u32 dat;

	dat = readl(led->led_virt + LED_DAT);	
	dat &= GPM_LED0_ON;
	writel(dat, led->led_virt + LED_DAT);
}

void led_off(struct led_info_st *led)
{
	u32 dat;

	dat = readl(led->led_virt + LED_DAT);	
	dat |= GPM_LED0_OFF;
	writel(dat, led->led_virt + LED_DAT);
}
/////////////////////////////////////////////////////
void led_info_init(struct led_info_st *led)
{
	led->user = 0;
}

void led_info_exit(struct led_info_st *led)
{
	led->user = 0;
}
//////////////////////////////////////////////////////
struct led_info_st ledx;

int led_open(struct inode *no, struct file *fp)
{
	led_on(&ledx);	
	ledx.user++;

	return 0;
}

int led_release(struct inode *no, struct file *fp)
{
	led_off(&ledx);
	ledx.user--;

	return 0;
}

long led_ioctl(struct file *fp, unsigned int cmd, unsigned long flags)
{
	return 0;
}

int led_status_handle(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	return 0;
}

struct file_operations led_ops = {
	.open = led_open,
	.release = led_release,
	.unlocked_ioctl = led_ioctl,
};

int led_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *l_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if(!l_res){
		printk("l_res request error in %s %s\n", __FILE__, __FUNCTION__);
		goto l_res_get_error;
	}

	ledx.led_virt = ioremap(l_res->start, l_res->end - l_res->start + 1);	
	if(!ledx.led_virt){
		printk("led_virt remap error in %s %s\n", __FILE__, __FUNCTION__);
		goto led_ioremap_error;	
	}

	led_info_init(&ledx);	
	led_hrd_init(&ledx);

	ledx.misc.minor = LED_MINOR;
	ledx.misc.name = pdev->name;
	ledx.misc.fops = &led_ops;
	ret = misc_register(&ledx.misc);
	if(ret < 0){
		printk("misc_register_error\n");
		goto misc_register_error;
	}

	ledx.led = proc_mkdir("led", NULL);
	if(!ledx.led){
		printk("proc_mkdir error in %s %s\n", __FILE__, __FUNCTION__);
		goto proc_mkdir_error;
	}

	ledx.led_status = create_proc_read_entry("led_status", 0, ledx.led, led_status_handle, &ledx);
	if(!ledx.led_status){
		printk("proc_create error in %s %s\n", __FILE__, __FUNCTION__);
		goto create_proc_error;
	}

	return 0;

create_proc_error:
	remove_proc_entry("led", NULL);
proc_mkdir_error:
	misc_deregister(&ledx.misc);	
misc_register_error:
	led_hrd_exit(&ledx);
	led_info_exit(&ledx);
	iounmap(ledx.led_virt);
led_ioremap_error:
l_res_get_error:
	return -EBUSY;
}

int led_remove(struct platform_device *pdev)
{
	remove_proc_entry("led_status", NULL);
	remove_proc_entry("led", NULL);
	misc_deregister(&ledx.misc);	
	led_hrd_exit(&ledx);
	led_info_exit(&ledx);
	iounmap(ledx.led_virt);
	return 0;
}

int led_suspend(struct platform_device *pdev, pm_message_t state)
{
	ledx.led_con = readl(ledx.led_virt + LED_CON);
	ledx.led_dat = readl(ledx.led_virt + LED_DAT);

	return 0;
}

int led_resume(struct platform_device *pdev)
{
	writel(ledx.led_con, ledx.led_virt + LED_CON);
	writel(ledx.led_dat, ledx.led_virt + LED_DAT);

	return 0;
}

struct platform_driver led_drv = {
	.driver = {
		.name = "s3c-led",
		.owner = THIS_MODULE,
	},
	.probe = led_probe,
	.remove = led_remove,
	.suspend = led_suspend,
	.resume = led_resume,
};

static __init int led_init(void)
{
	return platform_driver_register(&led_drv);
}

static __exit void led_exit(void)
{
	platform_driver_register(&led_drv);
}

module_init(led_init);
module_exit(led_exit);

MODULE_AUTHOR("ZhiYongLi");
MODULE_DESCRIPTION("This Is A Test For Class");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
