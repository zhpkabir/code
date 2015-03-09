#include "common.h"
#include "regs.h"

int main(int argc, char *argv[])
{
	char year, mon, date, day, hour, min, sec;

	//rtc_set_current_time(12, 10, 8, 2, 15, 20, 10);

	while(1){
		rtc_get_current_time(&year, &mon, &date, &day, &hour, &min, &sec);

		printf("20%d-%d-%d-%d-%d-%d-%d \r", year, mon, date, day, hour, min, sec);
	}

	return 0;
}
