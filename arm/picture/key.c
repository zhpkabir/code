#include "common.h"
#include "regs.h"

extern int auto_flow_flag;

void __attribute__((interrupt("IRQ"))) do_key(void)
{

	switch(EINT0PEND & 0x3f){
		case 1:
			sound_updown(0);
			break;
		case 2:
			sound_updown(1);
			break;
		case 4:
			change_pic(1);
			break;
		case 8:
			auto_flow_flag++;
			if(auto_flow_flag == 2){
				auto_flow_flag = 0;
			}
//			change_pic(0);
			break;
		case 16:
			pic_flow(1);
			break;
		case 32:
			pic_flow(0);
			break;
		default:
			break;
	}

	EINT0PEND = EINT0PEND;
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

int key_int_init(void)
{
	GPNCON &= ~(0xfff);
	GPNCON |= 0xaaa;

	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x222;

	EINT0MASK &= ~(0x3f);
	EINT0FLTCON0 = 0x80808080;

	irq_request(0, do_key);
	irq_request(1, do_key);

	return 0;
}

