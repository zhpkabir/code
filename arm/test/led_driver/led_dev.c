#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
#include "s3c_led.h"

void led_release(struct device *dev)
{
	
}

struct resource led_res[] = {
	[0] = {
		.start = S3C_PA_LED,
		.end = S3C_PA_LED + S3C_SZ_LED - 1,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device led_dev = {
	.name = "s3c-led",
	.id = -1,
	.num_resources = ARRAY_SIZE(led_res),
	.resource = led_res,
	.dev = {
		.platform_data = NULL,
		.release = led_release,	
	}
};

static __init int led_init(void)
{
	return platform_device_register(&led_dev);
}

static __exit void led_exit(void)
{
	platform_device_unregister(&led_dev);
}

module_init(led_init);
module_exit(led_exit);

MODULE_AUTHOR("ZhiYongLi");
MODULE_DESCRIPTION("This Is A Test For Class");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
