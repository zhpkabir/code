#include "common.h"

int main(int argc, char *argv[])
{
	int i, j;

	lcd_init();

	for(i = 0; i < 100; i++)
		for(j = 0; j < 100; j++)
			draw_point(i, j, 0x1f, 0, 0);
	
	return 0;
}
