#include <string.h>
#include<strings.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define port 1234
int main(int argc, char const *argv[])
{
	int sfd;
	struct sockaddr_in server;
	socklen_t len;
	char buff[100];
	sfd = socket(AF_INET,SOCK_DGRAM,0);
	len = sizeof(server);
	if(sfd!=-1)
		printf("Socket Created \n");
	server.sin_family  = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr  = inet_addr("127.0.0.1");
	//sendto(sfd,"Hello",sizeof("Hello"),0,(struct sockaddr*)&server,len);

	while(1)
	{
		printf("Enter String\n");
		scanf("%s",buff);
		sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&server,len);

		if(!strcmp(buff,"halt"))
		{
			break;
		}


		recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&server,&len);
		printf("%s\n",buff);
		int strleng;
		recvfrom(sfd,&strleng,sizeof(strleng),0,(struct sockaddr*)&server,&len);
		printf("String Length: %d\n",strleng);
		int counti[5];
		recvfrom(sfd,counti,sizeof(counti),0,(struct sockaddr*)&server,&len);
		
		printf("No of a: %d\n",counti[0]);
		printf("No of e: %d\n",counti[1]);
		printf("No of i: %d\n",counti[2]);
		printf("No of o: %d\n",counti[3]);
		printf("No of u: %d\n",counti[4]);

	}

	close(sfd);
	return 0;
}