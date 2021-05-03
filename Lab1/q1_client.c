#include <string.h>
#include<strings.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define port 1234

int main()
{
	int sfd;
	struct sockaddr_in server;
	socklen_t len;
	int buff[50];
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd!=-1)
		printf("Socket Created \n");
	server.sin_family  = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr  = inet_addr("127.0.0.1");
	int r = connect(sfd,(struct sockaddr*)&server,sizeof server);
	if(r!=-1)
	{
		printf("Connection Established with Server\n");
	}
	/*send(sfd,buff,sizeof(buff),0);
	recv(sfd,buff,sizeof(buff),0);.
	printf("Message From Server: %s",buff);
	close(sfd);*/
	while(1)
	{
		int n,choice,i,x=-1,num;
		int odd[50],even[50],n1,n2;
		if(x==0)
			break;
		
		printf("Enter Array Length: ");
		scanf("%d",&n);
		
		printf("Enter Elements of Array\n");
		for(i=0;i<n;i++)
			scanf("%d",&buff[i]);
		

		printf("Enter Choice: \n1-Sort | 2-Find | 3-Split to odd and even: \n");
		scanf("%d",&choice);
		write(sfd,&choice,sizeof(choice));

		write(sfd,&n,sizeof n);
		send(sfd,buff,sizeof buff,0);

		switch(choice)
		{
			case 1:
			read(sfd,buff,sizeof buff);
			printf("Sorted Array: ");
			for(i=0;i<n;i++)
			{
				printf("%d ",buff[i]);
			}
			break;

			case 2:
			printf("Enter Number To Find: \n");
			scanf("%d",&num);
			write(sfd,&num,sizeof num);
			read(sfd,&num,sizeof num);
			if(num!=-1)
				printf("Found At Position: %d\n",num+1);
			else
				printf("Element not found\n");
			break;

			case 3:
			read(sfd,&n1,sizeof(int));
			read(sfd,&n2,sizeof(int));
			read(sfd,even,sizeof(even));
			read(sfd,odd,sizeof(odd));

			printf("Even Array: ");
			for(i=0;i<n1;i++)
				printf("%d ",even[i]);
			printf("\n");
			printf("Odd Array: ");
			for(i=0;i<n2;i++)
				printf("%d ",odd[i]);
			printf("\n");

		}
		printf("Do u want to continue: 1/0:\n");
		int ch;
		fflush(stdin);
		scanf("%d",&ch);
		if(ch!=1)
		{
			choice=0;
			write(sfd,&choice,sizeof(choice));
			break;
		}

	}
	close(sfd);

}