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

int countOccurrences(char *filecontents,char *buff)
{
	int l = strlen(buff);
	int ans=0,x=0,i;
	int tl = strlen(filecontents);
			
			for(i=0;i<tl;i++)
			{
				if(filecontents[i]==buff[x])
				{
					x++;
				}
				else
				{
					i = i-x;
					x=0;
				}
				if(x==l)
				{
					x=0;
					ans+=1;
				}
			}
	return ans;
}

int replaceAll(char *str,char *old,char *new)
{
	char *pos,temp[500];
	int index=0;
	int oldlen = strlen(old);
	//printf("%s\n",str);
	int x=0;
	while((pos = strstr(str,old))!=NULL)
	{
		x++;
		index = pos - str;
		strcpy(temp,str);
		//printf("%s\n",str+oldlen );

		str[index] = '\0';
		strcat(str,new);
		strcat(str,temp+index+oldlen);
	}
	if(x!=0)
		return 1;
	return 0;
}


void bubbleSort(char strData[100][100],int noOfLines)
{
	int i,j;
	char strTempData[100];
	for(i= 0; i < (noOfLines - 1); ++i) {
        for(j = 0; j < ( noOfLines - i - 1); ++j) {
            if(strcmp(strData[j], strData[j+1]) > 0) {
                strcpy(strTempData, strData[j]);
                strcpy(strData[j], strData[j+1]);
                strcpy(strData[j+1], strTempData);
            }
        }
    }
}

int main()
{
	int s,ns,r;
	char buff[100];
	struct sockaddr_in server,client;
	socklen_t len;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s!=-1)
		printf("Socket Created \n");
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	//server.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_aton("127.0.0.1",&server.sin_addr);
	r = bind(s,(struct sockaddr*) &server,sizeof(server));
	if (r!=-1)
		printf("Socket Binded \n");
	r = listen(s,5);
	if (r!=-1)
		printf("Socket Listening \n");
	len = sizeof(client);
	ns = accept(s,(struct sockaddr *)&client,&len);
	if(ns!=-1)
		printf("Client Accepted\nConnection Establised\n");
	while(1)
	{
		read(ns,buff,sizeof buff);
		printf("File Name Recieved: %s\n",buff);
		FILE *f;
		f = fopen(buff,"r");
		if(f==NULL)
		{
			char temp[]="File not present";
			write(ns,temp,sizeof temp);

			break;
		}
		char temp2[] = "Enter 1. Search 2. Replace 3. Reorder 4. Exit: ";
		write(ns,temp2,sizeof temp2);
		int x=0,i;
		char c;
		int l;
		char filecontents[5000];
		// while(c=getc(f)!=EOF)
		// {
		// 	filecontents[x++] = c;
		// 	printf("%c",c);
		// }
		

		//filecontents[x] = '\n';
		//printf("File Contents: %s\n",filecontents);
		int choice;
		read(ns,&choice,sizeof choice);
		printf("Selected Choce: %d\n",choice);
		char buf1[100],buf2[100];
		int tl = strlen(filecontents),ans=0,ans1=0;
		switch(choice)
		{
			case 1:
			read(ns,buff,sizeof buff);
			while(fgets(filecontents,5000,f)!=NULL)
			{
				ans+=countOccurrences(filecontents,buff);
				//char *c1;
				// while((c1 = strstr(filecontents,buff))!=NULL)
				// 	ans1+=1;
			}
			/*char *c1=strstr(filecontents,buff);
			if(c1!=NULL)
			{
				printf("FOUND!!! %c\n",*c1);
			}*/
			//printf("%d\n",ans1);
			write(ns,&ans,sizeof ans);
			break;

			case 2:
			i=0;
			while((c = (char)getc(f))!=EOF)
			{
				filecontents[i++] = c;
			}
			filecontents[i]='\0';
			//printf("%s\n",filecontents);
			fclose(f);

			read(ns,buf1,sizeof buf1);
			read(ns,buf2,sizeof buf2);
			//printf("%s\n",filecontents );

			i = replaceAll(filecontents,buf1,buf2);
			//printf("%s\n",filecontents );
			if(i)
			{
				FILE *f2;
				f2 = fopen(buff,"w");
				fputs(filecontents,f2);
				char temp3[] = "String Replaced";
				write(ns,temp3,sizeof temp3);
			}
			else
			{
				char temp4[] = "String not found";
				write(ns,temp4,sizeof temp4);
			}
			break;
			case 3:
			i=0;
			while((c = (char)getc(f))!=EOF)
			{
				filecontents[i++] = c;
			}
			filecontents[i]='\0';

			char ch5[100][100];
			char *token=strtok(filecontents," ");
			i=0;
			while(token!=NULL)
			{
				//printf("%s\n",token );
				strcpy(ch5[i++],token);
				token=strtok(NULL," ");
			}
			bubbleSort(ch5,i);
			
			int z;
			char buff9[100];
			for(z=0;z<i;z++)
			{
				char b[1000];
				sprintf(b,"%s ",ch5[z]);
				strcat(buff9,b);
			}
			fclose(f);
			FILE *f3;
			f3 = fopen(buff,"w");
			fputs(buff9,f3);
			break;

			case 4:
			close(ns);
			close(s);
			exit(0);

		}
	}
	close(ns);
	close(s);
	return 0;
}