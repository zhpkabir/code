#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "proto.h"

int main(int argc,char *argv[])
{
	int sd;
	char sbuf[1024];
	struct sockaddr_in raddr;

	sd = socket(AF_INET,SOCK_DGRAM , 0);
	if(sd < 0)
	{
		perror("socket()");
		exit(1);
	}
	
	memset(&sbuf,'\0',sizeof(sbuf));
	strcpy(sbuf, "Hello Dm9000\n");
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT)); 
	if(inet_pton(AF_INET,"192.168.1.20",&raddr.sin_addr) != 1)
	{
		fprintf(stderr,"Bad address.!\n");
		exit(1);
	}
	while(1){

		if(sendto(sd,&sbuf,sizeof(sbuf),0,(void *)&raddr,sizeof(raddr)) < 0)
		{
			perror("sendto()");
			exit(1);
		}
		sleep(1);
	}
	puts("ok");
	
	close(sd);

	return 0;
}







