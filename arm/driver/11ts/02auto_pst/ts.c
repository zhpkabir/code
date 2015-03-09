#include "common.h"
#include "adc.h"

void ts_init(void)
{
	adc_init();
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



