#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define port 12334

int main(int argc, char const *argv[])
{
	/* code */
	int s,ns,r,len;
	struct sockaddr_in server,client;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s!=-1)
	{
		printf("Socket Created\n");
	}
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_aton("127.0.0.1",&server.sin_addr);
	r = bind(s,(struct sockaddr*)&server,sizeof server);
	if(r!=-1)
		printf("Socket Binded\n");
	r = listen(s,5);
	if(r!=-1)
		printf("Socket Listening\n");
	len = sizeof(client);
	ns = accept(s,(struct sockaddr*)&client,&len);
	if(ns!=-1)
	{
		printf("Client Accepted");
	}
	int pid=fork();
	printf("%d %d\n",pid,getppid());
	char buff[100];
	while(1)
	{
		if(pid>0)
		{
			read(ns,buff,sizeof buff);
			if(strcmp(buff,"exit")==0)
			{
				//printf("\nHello Exiting\n");
				write(ns,buff,sizeof buff);
				close(ns);
				close(s);
				exit(0);
			}
			char temp[] = "From Client: ";
			printf("%s %s\n",temp,buff);
		}
		if(pid==0)
		{
			printf("Enter Message: ");
			scanf("%s",buff);
			write(ns,buff,sizeof buff);
		}
	}
	return 0;
}