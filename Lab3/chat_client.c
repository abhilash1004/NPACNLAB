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
	int s;
	struct sockaddr_in server;
	socklen_t len;
	char buff[100];
	s = socket(AF_INET,SOCK_STREAM,0);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	inet_aton("127.0.0.1",&server.sin_addr);
	if(s!=-1)
		printf("Socket Created \n");
	len = sizeof(server);
	int r = connect(s,(struct sockaddr*)&server,len);
	if(r!=-1)
	{
		printf("Connection Established with Server\n");
	}
	int pid = fork();
	printf("%d %d\n",pid,getppid());
	while(1)
	{
		if(pid>0)
		{
			
			read(s,buff,sizeof buff);
			if(strcmp(buff,"exit")==0)
			{
				//printf("HEy\n");
				close(s);
				//x=1;
				exit(0);
			}
			char temp[] = "From Server: ";
			printf("%s %s\n",temp,buff);
		}
		if(pid==0)
		{
			printf("Enter Message: ");
			scanf("%s",buff);
			write(s,buff,sizeof buff);
			//printf("%s\n",buff);
			
		}
	}
	return 0;
}