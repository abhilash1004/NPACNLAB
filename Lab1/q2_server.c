#include <string.h>
#include<strings.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define port 1234
int checkPalindrome(char *str)
{
	int n = strlen(str);
	int i;
	for(i=0;i<n/2;i++)
	{
		if(str[i]!=str[n-i-1])
			return 0;
	}
	return 1;
}
void countVowels(int *vow,char *str)
{
	//printf("Copunted\n");
	int n = strlen(str);
	int i;
	for(i=0;i<n;i++)
	{
		switch(str[i])
		{
			case 'a':
			vow[0]++;
			break;
			case 'e':
			vow[1]++;
			break;
			case 'i':
			vow[2]++;
			break;
			case 'o':
			vow[3]++;
			break;
			case 'u':
			vow[4]++;
			break;
		}
	}
	//printf("adnjhf\n");

}

int main(int argc, char const *argv[])
{
	int s,r,len;
	struct sockaddr_in server,client;
	char buff[100];
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s!=-1)
		printf("Socket Created \n");
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(client);
	r = bind(s,(struct sockaddr*)&server,sizeof server);
	if (r!=-1)
		printf("Socket Binded \n");
	/*recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&len);
	printf("Message Recieved From Client: %s\n",buff);*/
	while(1)
	{
		recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&len);
		printf("String Recieved\n");
		if(!strcmp(buff,"halt"))
		{
			break;
		}

		int ans=checkPalindrome(buff);
		int strleng = strlen(buff);
		if(ans)
		{
			sendto(s,"It is a palindrome",sizeof("It is a palindrome"),0,(struct sockaddr*)&client,len);
		}
		else
		{
			sendto(s,"It is not a palindrome",sizeof("It is not a palindrome"),0,(struct sockaddr*)&client,len);
		}
		sendto(s,&strleng,sizeof(strleng),0,(struct sockaddr*)&client,len);
		int counti[5]={0};
		countVowels(counti,buff);
		sendto(s,counti,sizeof(counti),0,(struct sockaddr*)&client,len);
		
	}
	close(s);
	return 0;
}