#include "common.h"
#include "adc.h"

#define INT_PENDNUP 62

void ts_init(void)
{
	adc_init();
}

void wait_for_dn(void)
{
	ADCTSC = 0xd3;	
}

void wait_for_up(void)
{
	ADCTSC = 0xd3 | (1 << 8);
}

void __attribute__((interrupt("IRQ"))) do_adc(void)
{
	printf("x = %d, y = %d\n", ADCDAT0 & 0xfff, ADCDAT1 & 0xfff);
	
	wait_for_up();
	clear_int();
	ADCCLRINT = 1;
}

void __attribute__((interrupt("IRQ"))) do_updn(void)
{
	if(ADCUPDN & 1){
		//down
		ADCTSC = 1 << 2;
		start_adc();
		ADCUPDN = 0;
	}else if(ADCUPDN & 2){
		//up
		ADCUPDN = 0;
		printf("TS UP\n");
		wait_for_dn();
	}else{
		//do nothing
	}
	clear_int();
	ADCCLRINTPNDNUP = 1;
}

void auto_pst(int *x, int *y)
{
	ADCTSC = 1 << 2;
	start_adc();
	end_adc();
	
	*x = ADCDAT0 & 0xfff;
	*y = ADCDAT1 & 0xfff;
}

int return_x(void)
{
	ADCTSC = 1;
	start_adc();
	end_adc();
	
	return ADCDAT0 & 0xfff;
}

int return_y(void)
{
	ADCTSC = 2;
	start_adc();
        end_adc();

        return ADCDAT1 & 0xfff;
}



