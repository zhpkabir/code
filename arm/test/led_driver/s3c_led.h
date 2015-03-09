#ifndef S3C_LED_H
#define S3C_LED_H

#include <linux/miscdevice.h>

struct led_info_st {
	void __iomem *led_virt;
	struct proc_dir_entry *led;
	struct proc_dir_entry *led_status;
	u32 user;
	u32 led_con;
	u32 led_dat;
	struct miscdevice misc;
};

#define LED_MINOR	20

#define S3C_PA_LED	0x7F008000
#define S3C_SZ_LED	SZ_4K

#define LED_CON		0x820
#define LED_DAT		0x824
#define LED_PUD		0x828

#define GPM_LED_MASK	~0xffff
#define GPM_LED_OUT	0x1111

#define GPM_LED0_ON	~1
#define GPM_LED1_ON	~(1 << 1)
#define GPM_LED2_ON	~(1 << 2)
#define GPM_LED3_ON	~(1 << 3)
#define GPM_LED_ALL_OFF	(0xf)

#define GPM_LED0_OFF	1
#define GPM_LED1_OFF	(1 << 1)
#define GPM_LED2_OFF	(1 << 2)
#define GPM_LED3_OFF	(1 << 3)

#define S3C_LED_ON	1
#define S3C_LED_OFF	0

#endif
