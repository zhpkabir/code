#include <linux/module.h>     
#include <linux/kernel.h>     
#include <linux/errno.h>      
#include <linux/err.h>        
#include <linux/fb.h>         
#include <linux/init.h>       
#include <linux/semaphore.h>  
#include <linux/mm.h>         
#include <linux/dma-mapping.h>
#include <linux/delay.h>      
#include <linux/hrtimer.h>   
#include <linux/time.h>       
  
static struct hrtimer vibe_timer;  
static struct work_struct vibe_work;  
  
static void vibe_work_func(struct work_struct *work)  
{  
    printk("vibe_work_func:msleep(50)\n");  
    msleep(50);
}  
  
static enum hrtimer_restart vibrator_timer_func(struct hrtimer *timer)   
{             
    struct timespec uptime;  
      
    do_posix_clock_monotonic_gettime(&uptime);  
    printk("Time:%lu.%02lu\n", (unsigned long) uptime.tv_sec, (uptime.tv_nsec / (NSEC_PER_SEC / 100)));  
    printk("vibrator_timer_func\n");   
    schedule_work(&vibe_work);  
    return HRTIMER_NORESTART;  
}  
  
static int __init ker_driver_init(void)  
{  
    struct timespec uptime;  
      
    printk("ker_driver_init\n");  
    hrtimer_init(&vibe_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);  
    vibe_timer.function = vibrator_timer_func;  
    hrtimer_start(&vibe_timer, ktime_set(2, 0), HRTIMER_MODE_REL);  
    do_posix_clock_monotonic_gettime(&uptime);  
    printk("Time:%lu.%02lu\n", (unsigned long) uptime.tv_sec, (uptime.tv_nsec / (NSEC_PER_SEC / 100)));  
    INIT_WORK(&vibe_work, vibe_work_func); 
    return 0;  
}  
  
static void __exit ker_driver_exit(void)  
{  
    hrtimer_cancel(&vibe_timer);  
}  
  
module_init(ker_driver_init);  
module_exit(ker_driver_exit);  
  
MODULE_AUTHOR("Woodpecker <Pecker.hu@gmail.com>");  
MODULE_DESCRIPTION("Kernel driver");  
MODULE_LICENSE("GPL");
