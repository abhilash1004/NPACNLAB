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

int main(int argc, char const *argv[])
{
	/* code */

	int s;
	struct sockaddr_in server;
	socklen_t len;
	char buff[100];
	s = socket(AF_INET,SOCK_DGRAM,0);
	len = sizeof(server);
	if(s!=-1)
		printf("Socket Created \n");
	server.sin_family  = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr  = inet_addr("127.0.0.1");

	while(1)
	{
		printf("Enter The File Name\n");
		scanf("%s",buff);
		//write(s,buff,sizeof buff);
		sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&server,len);
		//read(s,buff,sizeof buff);
		recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&server,&len);

		if(!strcmp(buff,"File not present"))
		{
			printf("%s\n",buff);
			break;
		}
		printf("%s\n",buff);
		int choice;
		scanf("%d",&choice);
		//write(s,&choice,sizeof(choice));
		sendto(s,&choice,sizeof(choice),0,(struct sockaddr*)&server,len);

		int ans;
		char buf1[100],buf2[100];
		switch(choice)
		{
			case 1:
			printf("Enter String to be searched: \n");
			scanf("%s",buff);
			//write(s,buff,sizeof buff);
			sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&server,len);

			//read(s,&ans,sizeof ans);
			recvfrom(s,&ans,sizeof(ans),0,(struct sockaddr*)&server,&len);

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
			//write(s,buf1,sizeof buf1);
			//write(s,buf2,sizeof buf2);
			sendto(s,buf1,sizeof(buf1),0,(struct sockaddr*)&server,len);
			sendto(s,buf2,sizeof(buf2),0,(struct sockaddr*)&server,len);

			//read(s,buf1,sizeof buf1);
			recvfrom(s,buf1,sizeof(buf1),0,(struct sockaddr*)&server,&len);
			printf("%s\n",buf1);
			break;

			case 4:
			close(s);
			exit(0);
			break;
		}
	}
	return 0;
}