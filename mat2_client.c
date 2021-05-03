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
	int s,r,len;
	struct sockaddr_in server;
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
	r=connect(s,(struct sockaddr*)&server,sizeof server);
	printf("Connection Established\n");
	int ans[100][100],m,n;
	read(s,ans,sizeof(ans));
	read(s,&m,sizeof m);
	read(s,&n,sizeof n);
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\n",ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}