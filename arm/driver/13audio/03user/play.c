#include <linux/soundcard.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, s_fd;
	int channels = 2;
	int bit = 16;
	int rate = 44100;
	int ret;

	fd = open("/dev/dsp", O_RDWR);
	if(fd < 0)
		perror("open /dev/dsp");


	ret = ioctl(fd, SOUND_PCM_WRITE_BITS, &bit);
	if(ret < 0)
		perror("ioctl SOUND_PCM_WRITE_BITS");

	ret = ioctl(fd, SOUND_PCM_WRITE_RATE, &rate);
	if(ret < 0)
		perror("ioclt SOUND_PCM_WRITE_RATE");

	ret = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &channels);
	if(ret < 0)
		perror("ioctl SOUND_PCM_WRITE_CHANNELS");
	
	s_fd = open(argv[1], O_RDONLY);
	if(s_fd < 0)
		perror("open s_fd");	

	char buf[44100 * 2 * 2 * 5];

	while(1){
		ret = read(s_fd, buf, sizeof(buf));
		printf("ret = %d %d\n", ret, sizeof(buf));
		if(ret == 0)
			break;
		write(fd, buf, ret);
	}

	close(s_fd);
	close(fd);
	
	return 0;
}
