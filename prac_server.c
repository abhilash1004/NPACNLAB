#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define port 1234

void replace_all(char *str,char *old,char *new)
{
	int l = strlen(old);
	char *p;
	int pos;
	char temp[100];
	while((p = strstr(str,old))!=NULL)
	{
		pos = p - str;
		strcpy(temp,str);
		str[pos] = '\0';
		strcat(str,new);
		strcat(str,temp+pos+l);
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	int s,r,ns;
	struct sockaddr_in server,client;
	int len;
	s = socket(AF_INET,SOCK_STREAM,0);

	server.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//inet_aton("127.0.0.1",&server.sin_addr);
	server.sin_addr.s_addr =htonl(INADDR_ANY);
	server.sin_port = htons(1234);
	r = bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r!=-1)
		printf("Binded Successfully\n");
	r=listen(s,5);
	if(r!=-1)
		printf("Listening Successfully\n");
	len = sizeof(client);
	ns = accept(s,(struct sockaddr*)&client,&(len));
	if(ns!=-1)
		printf("Client Accepted\n");
	char str[100];
	strcpy(str,inet_ntoa(client.sin_addr));
	strcat(str,":");
	char temp[1000];
	sprintf(temp,"%d",ntohs(server.sin_port));
	strcat(str,temp);
	//printf("%s\n",);
	puts(str);

	FILE *f1;
	f1 = fopen("sample.txt","w");
	if(f1==NULL)
	{
		exit(0);
	}
	fputs(str,f1);
	replace_all(str,".","dot");
	replace_all(str,":","colon");
	printf("\n%s\n",str);

	close(ns);
	close(s);
	return 0;
}