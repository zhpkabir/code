#include "common.h"
#include "regs.h"

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

