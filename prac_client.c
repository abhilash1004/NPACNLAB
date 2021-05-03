#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define port 1234

int main(int argc, char const *argv[])
{
	/* code */
	int sockfd;
	socklen_t len;
	struct sockaddr_in servAddr;
	char buffer[1024];

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(1234);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(servAddr.sin_zero,'\0',sizeof servAddr.sin_zero);

	len = sizeof servAddr;

	int x=connect(sockfd,(struct sockaddr *)&servAddr,len);
	close(sockfd);
	return 0;
}