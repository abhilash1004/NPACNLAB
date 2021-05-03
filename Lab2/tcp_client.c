#include <string.h>
#include<strings.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define port 12345

int main()
{
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

	while(1)
	{
		printf("Enter The File Name\n");
		scanf("%s",buff);
		write(s,buff,sizeof buff);
		read(s,buff,sizeof buff);
		if(!strcmp(buff,"File not present"))
		{
			printf("%s\n",buff);
			break;
		}
		//read(s,buff,sizeof buff);
		printf("%s\n",buff);
		int choice;
		scanf("%d",&choice);
		write(s,&choice,sizeof(choice));
		int ans;
		char buf1[100],buf2[100];
		switch(choice)
		{
			case 1:
			printf("Enter String to be searched: \n");
			scanf("%s",buff);
			write(s,buff,sizeof buff);

			read(s,&ans,sizeof ans);
			if(ans==0)
				printf("No occurences of %s\n",buff);
			else
				printf("%d occurences of %s\n",ans,buff);
			break;

			case 2:
			printf("Enter String to be replaced: ");
			scanf("%s",buf1);
			//fgets(buf1);
			printf("Enter String to be placed: ");
			scanf("%s",buf2);
			//fgets("%s",buf2);
			write(s,buf1,sizeof buf1);
			write(s,buf2,sizeof buf2);

			read(s,buf1,sizeof buf1);
			printf("%s\n",buf1);
			break;

			case 4:
			close(s);
			exit(0);
			break;
		}
	}
	close(s);
}