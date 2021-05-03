#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>


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



int main()
{
int s,r,recb,sntb,x,ns;
printf("Input Port Number: ");
scanf("%d",&x);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
int a[10] = {0};
char name[100],id[100],bs[100];
printf("Enter employee name: ");
scanf("%s",name);
printf("Enter employee id: ");
scanf("%s",id);
printf("Enter employee salary: ");
scanf("%s",bs);
char st[100];
strcat(st,id);
strcat(st," ");
strcat(st,name);
strcat(st," ");
strcat(st,bs);
strcat(st,"\n");
FILE *f;
f = fopen("emp.txt","w+");
fputs(st,f);
fclose(f);


s = socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("Socket Creation Failed\n");
exit(0);
}
printf("Socket Created\n");


server.sin_family = AF_INET;
server.sin_port = htons(x);
server.sin_addr.s_addr = htonl(INADDR_ANY);
r = bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("Binding Failed\n");
close(s);
exit(0);
}
printf("Socket Binded\n");


r = listen(s,1);
if(r==-1)
{
printf("Listen Failed\n");
close(s);
exit(0);
}
printf("Socket Listening\n");
len = sizeof(client);


ns = accept(s,(struct sockaddr*)&client,&len);
if(ns==-1)
{
printf("Accept Failed\n");
close(s);
exit(0);
}
printf("Socket Accepting\n");


/*recb = recv(ns,a,sizeof(a),0);

if(recb==-1)
{
printf("Message Received Failed\n");
close(ns);
close(s);
exit(0);
}*/

while(a[1]!=4)
{
recb = recv(ns,a,sizeof(a),0);

if(recb==-1)
{
printf("Message Received Failed\n");
close(ns);
close(s);
exit(0);
}


if(a[1]==2)
{
FILE *f;
f = fopen("emp.txt","r+");
char con[5000];
while(fgets(con,5000,f)!=NULL)
{
if((con[0] - '0') == a[0])
{printf("%s\n",con);}
}
fclose(f);
}

char buf1[1000],buf2[1000],buf[5000];
if(a[1]==3)
{
printf("Updated\n");
FILE *f,*f2;
f = fopen("emp.txt","r");
printf("123\n");
read(ns,buf,sizeof(buf));
printf("%s\n",buf);
int i=0,j=0;
char *tok1 = strtok(buf," ");
/*printf("Buf1: %s\t",buf1);
printf("Buf2: %s\t",buf2);*/
char c1[100][100];
/*char *tok1 = strtok(buf1," ");
char c2[100][100];
char *tok2 = strtok(buf2," ");*/
while(tok1!=NULL)
{
printf("Tok1\t");
strcpy(c1[i++],tok1);
tok1 = strtok(NULL," ");
}
/*while(tok2!=NULL)
{
printf("Tok1\t");
strcpy(c2[j++],tok2);
tok2 = strtok(NULL," ");
}*/

int bas1 = atoi(c1[2]);
int bas2 = atoi(c1[5]);
printf("%d %d",bas1,bas2);
float sum1 = (bas1 + (0.25*bas1) - (0.10 * bas1));
float sum2 = (bas2 + (0.25*bas2) - (0.10 * bas2));
char basi1[100]; 
char basi2[100];
/*itoa(sum1,basi1,10);
itoa(sum2,basi2,10);*/
sprintf(basi1,"%f",sum1);
sprintf(basi2,"%f",sum2);

int l,m;
l = replaceAll(buf1,c1[2],basi1);
m = replaceAll(buf2,c1[5],basi2);

if(l==1&m==1)
{
fputs(buf1,f);
fputs(buf2,f);
char temp3[] = "Salary Updated";
write(ns,temp3,sizeof temp3);
}
else
{
char temp4[] = "Salary not found";
write(ns,temp4,sizeof temp4);
}
fclose(f);
}

}



close(ns);
close(s);
return 0;
}

