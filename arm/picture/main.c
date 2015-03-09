#include "common.h"
#include "regs.h"

extern int auto_flow_flag;

int main(int argc, char **argv)
{
	int i = 0;

	uart_init();

	lcd_init();
	nand_read(FRAMEBUFFER, 0x4500000, WIDE * LONG * 4 * (MAX_NUM + 1));
	nand_read(FRAMEBUFFER1, 0x5000000, WIDE * LONG * 4);

	key_int_init();
	touch_init();

	ac97_init();
	wm9714_init();
	play_music(0x52000000, 220 * 44100 * 2 * 2);
	nand_read(0x52000000, 0x40000, 0x3000000);

	while(1){
		led_on(i);
		delay(100);
		led_off(i);
		delay(100);
		i++;
		if(i == 4){
			i = 0;
		}
		if(auto_flow_flag == 1){
			VIC0INTENCLEAR |= (1 << 1);
			VIC1INTENCLEAR |= (1 << 30);
			EINT0MASK |= 1 << 2;
			while(1){
				pic_flow(1);
				if(auto_flow_flag == 0){
					VIC0INTENABLE |= (1 << 1);
					VIC1INTENABLE |= (1 << 30);
					EINT0MASK &= ~(1 << 2);
					break;
				}
				delay(80);
			}
		}
	}

	return 0;
}


