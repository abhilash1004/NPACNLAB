#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define port 12345

int main(int argc, char const *argv[])
{
	/* code */
	int s,ns,r,len;
	struct sockaddr_in client,server;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s!=-1)
	{
		printf("Socket Created\n");
	}
	else
	{
		printf("Error\n");
		exit(0);
	}
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	r = bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r!=-1)
	{
		printf("Bind Successfull\n");
	}
	else
	{
		printf("Error\n");
		exit(0);
	}
	r = listen(s,5);
	if(r!=-1)
	{
		printf("Socket Listening...\n");
	}
	else
	{
		printf("Error\n");
		exit(0);
	}
	//len = sizeof(client);
	ns = accept(s,(struct sockaddr*)&client,&len);
	if(ns!=-1)
	{
		printf("Client Accepted\n");
	}
	else
	{
		printf("Error\n");
		exit(0);
	}
	int m1[100][100],m2[100][100];
	FILE *f1,*f2;
	f1 = fopen("M1.txt","r");
	f2 = fopen("M2.txt","r");
	char str[100];
	int i=0,j;
	while(fgets(str,100,f1)!=NULL)
	{
		char *token = strtok(str," ");
		j=0;
		while(token!=NULL)
		{
			m1[i][j] = atoi(token);
			token = strtok(NULL," ");
			j++;
		}
		i++;
	}
	int x1=i,y1=j;
	i=0;
	while(fgets(str,100,f2)!=NULL)
	{
		char *token = strtok(str," ");
		j=0;
		while(token!=NULL)
		{
			m2[i][j] = atoi(token);
			token = strtok(NULL," ");
			j++;
		}
		i++;
	}
	int x2=i,y2=j;
	if(y1!=x2)
	{
		printf("Cant Multipy Matrices\n");
		exit(0);
	}
	int k;
	int mat[100][100];
	for(i=0;i<x1;i++)
	{
		for(j=0;j<y2;j++)
		{
			mat[i][j]=0;
			for(k=0;k<y1;k++)
			{
				mat[i][j]+=m1[i][k]+m2[k][j];
			}
		}
	}
	write(ns,mat,sizeof mat);
	write(ns,&x1,sizeof x1);
	write(ns,&y2,sizeof y2);
	for(i=0;i<x1;i++)
	{
		for(j=0;j<y2;j++)
		{
			printf("%d\n",mat[i][j]);
		}
		printf("\n");
	}

	return 0;
}