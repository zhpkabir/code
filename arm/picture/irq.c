#include "common.h"
#include "regs.h"

/*S3C6410向量中断控制器原理：
 	当一个中断源产生中断后，首先这个中断信号会到达6410当中的
 	中断控制器，然后中断控制器查询VICxINTENABLE寄存器，该寄存
	器当中的每一位对应一个中断源(第n位对应n(或者n－32)号中断源)
 	如果该中断源对应的那一位为1，则代表该中断可以通过，如果通过
 	则控制器会把VICxIRQSTATUS寄存器中的第n位(或者n－1位)设置为1，
 	然后再去查询VIC0INTSELECT寄存器，查看要以什么样的中断方式向
 	CPU报告中断(如果该寄存器的n位是1,则代表快速中断,否则是普通中断)
 	查询完成后，控制器会把VICxVECTADDRn的值拷贝到VICxADDRESS中，
	然后PC调到内存的0x18地址去执行。
 */

int irq_request(int no, void (*handle)(void))
{
	if(no <= 31 && no >= 0){
		//打开中断，查看S3C6410手册P419
		VIC0INTENABLE |= 1 << no;
		//选择irq中断，查看S3C6410手册P418
		VIC0INTSELECT &= ~(1 << no);
		//填入中断处理函数入口地址，查看S3C6410手册P423
		VIC0VECTADDR[no] = (unsigned int)handle;
	}else if(no <= 63 && no >= 32){
		no -= 32;//
		VIC1INTENABLE |= 1 << no;//打开中断
                VIC1INTSELECT &= ~(1 << no);//选择irq中断
                VIC1VECTADDR[no] = (unsigned int)handle;//填入中断处理函数入口地址

	}else{
		return -1;
	}

	/*清除掉CPSR寄存器的I位，打开中断
	 *查看arm架构手册P49*/
	__asm__ __volatile__(
		"mrs r0, cpsr\n"		
		"bic r0, r0, #0x80\n"
		"msr cpsr, r0\n"
		:
		:
		:"r0"
	);

	return 0;
}

