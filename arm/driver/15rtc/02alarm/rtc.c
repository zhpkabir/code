#include "common.h"
#include "regs.h"

void rtc_set_current_time(char year, char mon, char data, \
		char day, char hour, char min, char sec)
{
	RTCCON = 1;
	
	BCDSEC = ((sec / 10) << 4) | (sec % 10);
	BCDMIN = ((min / 10) << 4) | (min % 10);
	BCDHOUR = ((hour / 10) << 4) | (hour % 10);
	BCDDATE = ((data / 10) << 4) | (data % 10);
	BCDDAY = day;
	BCDMON = ((mon / 10) << 4) | (mon % 10);
	BCDYEAR = ((year / 10) << 4) | (year % 10);

	RTCCON = 0;
}

void rtc_get_current_time(char *year, char *mon, char *data, \
		char *day, char *hour, char *min, char *sec)
{
again:
	*year = ((BCDYEAR >> 4) & 0xf) * 10 + (BCDYEAR & 0xf);
	*mon = ((BCDMON >> 4) & 1) * 10 + (BCDMON & 0xf);
	*day = BCDDAY & 0x7;
	*data = ((BCDDATE >> 4) & 3) * 10 + (BCDDATE & 0xf);
	*hour = ((BCDHOUR >> 4) & 3) * 10 + (BCDHOUR & 0xf);
	*min = ((BCDMIN >> 4) & 7) * 10 + (BCDMIN & 0xf);
	*sec = ((BCDSEC >> 4) & 7) * 10 + (BCDSEC & 0xf);
	if(*sec == 0){
		goto again;
	}
}

void rtc_set_alarm_time(char year, char mon, char data, \
		char hour, char min, char sec)
{
	ALMSEC = ((sec / 10) << 4) | (sec % 10);
	ALMMIN = ((min / 10) << 4) | (min % 10);
	ALMHOUR = ((hour / 10) << 4) | (hour % 10);
	ALMDATE = ((data / 10) << 4) | (data % 10);
	ALMMON = ((mon / 10) << 4) | (mon % 10);
	ALMYEAR = ((year / 10) << 4) | (year % 10);
	RTCALM = 0xff;
}



