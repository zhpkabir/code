#include "common.h"
#include "regs.h"

#define INT_RTC_ALARM 60

void do_rtc_alarm(void);

int main(int argc, char *argv[])
{
	char year, mon, date, day, hour, min, sec;

//	rtc_set_current_time(12, 4, 22, 7, 16, 38, 10);

	rtc_set_alarm_time(12, 10, 8, 15, 31, 10);
	irq_request(INT_RTC_ALARM, do_rtc_alarm);

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
