#include "common.h"
#include "adc.h"

void adc_init(void)
{
	//3MHz
	ADCCON = (1 << 16) | (1 << 14) | (21 << 6);
}

void end_adc(void)
{
	while(!(ADCCON & (1 << 15)));
}

void start_adc(void)
{
	ADCCON |= 1;
}

int return_adc(void)
{
	return ADCDAT0 & 0xfff;
}
