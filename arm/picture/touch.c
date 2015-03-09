#include "common.h"
#include "regs.h"

#define START_ADC	ADCCON |= 1
#define WAIT_DOWN	ADCTSC = (1 << 7) | (1 << 6) | (1 << 4) | 3
#define WAIT_UP		ADCTSC = (1 << 8) | (1 << 7) | (1 << 6) | (1 << 4) | 3
#define AUTO_PST	ADCTSC = 1 << 2
#define INT_ADC 	63
#define INT_PENDNUP 	62
#define INT_WDT		26
#define ENABLE_WDT	WTCON |= 1 << 5
#define DISABLE_WDT	WTCON &= ~(1 << 5)	

int if_next(void);

int new_x = 0;
int old_x = 0;
int flag = 0;
int ml[10] = {0};


void __attribute__((interrupt("IRQ"))) do_wdt(void)
{
	WTCLRINT = 1;
	AUTO_PST;
	START_ADC;
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

void __attribute__((interrupt("IRQ"))) do_adc(void)
{
	static int lm = 1;

	ADCCLRINT = 1;
	if(flag == 1){
		old_x = ADCDAT0 & 0xfff;
		flag = 0;
	}else{
		ml[lm++] = ADCDAT0 & 0xfff;
		if(lm == 10){
			lm = 0;
		}
		new_x = cal_val(ml, lm);
	}

	WAIT_UP;
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

void __attribute__((interrupt("IRQ"))) do_updown(void)
{
	if(ADCUPDN & 1){
		ADCUPDN = 0;
		flag = 1;
		ENABLE_WDT;
	}else if(ADCUPDN & 2){
		ADCUPDN = 0;
		DISABLE_WDT;
		change_pic(if_next());
		WAIT_DOWN;
	}

	ADCCLRINTPNDNUP = 1;
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

int if_next(void)
{
	if(new_x - old_x > 800){
		return 1;
	}else if(old_x - new_x > 800){
		return 0;
	}else{
		return 2;
	}
}

int cal_val(int *arr, int n)
{
	int sum = 0;
	int i;

	for(i = 0; i < 10; i++){
		if(i == n){
			continue;	
		}
		sum += arr[i];
	}	

	return (sum / 9);
}

int touch_init(int argc, char *argv[])
{
	flag = 1;
	/*operations*/
	ADCCON = (1 << 16) | (1 << 14) | (65 << 6);
	ADCDLY = 0xffff;

	wdt_init(10);

	irq_request(INT_PENDNUP, do_updown);
	irq_request(INT_ADC, do_adc);
	irq_request(INT_WDT, do_wdt);
	WAIT_DOWN;

	return 0;
}
