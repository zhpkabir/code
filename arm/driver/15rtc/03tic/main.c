#include "common.h"
#include "regs.h"

#define INT_RTC_ALARM 	60
#define INT_RTC_TIC 	2

void do_rtc_alarm(void);
void do_rtc_tic(void);

int main(int argc, char *argv[])
{
	char year, mon, date, day, hour, min, sec;

//	rtc_set_current_time(12, 4, 22, 7, 16, 38, 10);

//	rtc_set_alarm_time(12, 4, 22, 17, 29, 10);
//	irq_request(INT_RTC_ALARM, do_rtc_alarm);

//	rtc_set_tic_time(0xf, 1);
	rtc_set_tic_time(0xe, 1);
	irq_request(INT_RTC_TIC, do_rtc_tic);

	while(1){
		rtc_get_current_time(&year, &mon, &date, &day, &hour, &min, &sec);
		printf("The Current Time:");
		printf("20%d-%d-%d-%d-%d-%d-%d \r", year, mon, date, day, hour, min, sec);
	}

	return 0;
}

void __attribute__((interrupt("IRQ"))) do_rtc_alarm(void)
{
	if(INTP & 2){
		INTP |= 1 << 1;
		printf("\r\nalarm interrupt..\n");
	}
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}

void __attribute__((interrupt("IRQ"))) do_rtc_tic(void)
{
	if(INTP & 1){
		INTP |= 1;
		printf("\r\ntic interrupt..\n");
	}
	VIC0ADDRESS = 0;
	VIC1ADDRESS = 0;
}
