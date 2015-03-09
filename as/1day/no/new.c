#include <unistd.h>

int sb()
{
	write(1,"hello,world\n",12);
	return 0;
}
