/*
 * Author : ZhongHuiping
 * Email : zhonghuiping@tydtech.com
 * Last modified : 2014-02-24 20:34
 * Filename : app.c
 * Description : open dev node 
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd;
	int size;
	char buf[1024];

	fd = open(argv[1], O_RDWR);
	if(fd < 0){
		perror("open() error\n");
		exit(1);
	}

	size = write(fd, "Hello cdev\n", 1024);

	size = read(fd, buf, size);

	ioctl(fd, 1, NULL);

	printf("%s\n",buf);

	close(fd);

	return 0;
}
