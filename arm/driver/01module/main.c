#include "common.h"

int main(int argc, char *argv[])
{
	driver_init();
	ops();
	printf("Hello ARM!\n");

	return 0;
}
