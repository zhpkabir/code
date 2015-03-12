#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

static int fd;
static char buf[4];

void signal_handler(int sig)
{
	printf("get a signal\n");
	read(fd,buf,3);
	puts(buf);
}

int main()
{
	fd = open("/dev/kill",O_RDONLY);
	if (fd < 0)
		return -1;
	fcntl(fd, F_SETOWN, getpid());
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL)|O_ASYNC);
	signal(SIGIO, signal_handler);
	while(1)
	{
		sleep(2);
	}
	close(fd);
	return 0;
}
