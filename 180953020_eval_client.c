#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
int s,r,recb,sntb,x;
printf("Input Port Number: ");
scanf("%d",&x);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];


s = socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("Socket Creation Failed\n");
exit(0);
}
printf("Socket Created\n");

server.sin_family = AF_INET;
server.sin_port = htons(x);
server.sin_addr.s_addr = inet_addr("127.0.0.1");


r = connect(s,(struct sockaddr*)&server,sizeof(server));
if(r == -1)
{
printf("Connection Failed\n");
exit(0);
}
printf("Socket Connected\n");




int ch = 0;


while(ch!=4)
{
printf("Enter 1-insert 2-display 3-update 4-exit: ");
scanf("%d",&ch);
if(ch==1)
{
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
f = fopen("emp.txt","a+");
fputs(st,f);
fclose(f);
}

if(ch == 2)
{
int eid;
int a[2];
printf("Enter empid: ");
scanf("%d",&eid);
a[0] = eid;a[1] = ch;
send(s,a,sizeof(a),0);
}

if(ch == 3)
{
FILE *f;
int a[2];
f = fopen("emp.txt","r");
char contents[5000];
char buffi[5000];
char st1[5000];
int count = 0;
char c;
a[0] = ch;
a[1] = ch;
send(s,a,sizeof(a),0);
c = fgetc(f); 
    while (c != EOF) 
    { 
        st1[count] = c;
        count++;
        //printf ("%c", c); 
        c = fgetc(f); 
    } 
    st1[count] = '\0';
write(s,st1,sizeof(st1));
printf("End\n");
read(s,buffi,sizeof(buffi));
printf("buffi%s\n",buffi);
printf("\n\n\nHello\n");
fclose(f);
}
}
FILE *f;
f = fopen("emp.txt","r+");
char con[5000];
while(fgets(con,5000,f)!=NULL)
{
printf("%s\n",con);
}
fclose(f);
close(s);
return 0;
}
