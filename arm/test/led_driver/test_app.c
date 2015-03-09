#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	
	if(argc != 2)
		printf("Usage <%s> <dev>\n", argv[0]);

	fd = open(argv[1], O_RDWR);
	if(fd < 0)
		perror("open()");

	sleep(5);

	close(fd);

	return 0;
}
