#include <string.h>
#include<strings.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define port 1234

void insertionSort(int arr[], int n)  
{  
    int i, key, j;  
    for (i = 1; i < n; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}  

int main()
{
	int s,r;
	socklen_t len;
	struct sockaddr_in server,client;
	int buff[50];
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s!=-1)
		printf("Socket Created \n");
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	r = bind(s,(struct sockaddr*)&server,sizeof server);
	if (r!=-1)
		printf("Socket Binded \n");
	r = listen(s,5);
	if (r!=-1)
		printf("Socket Listening \n");
	len = sizeof client;
	int ns = accept(s,(struct sockaddr*)&client,&len);
	if(ns!=-1)
		printf("Client Accepted\nConnection Establised\n");
	else if (ns==-1)
	{
		printf("Error");
		exit(0);
	}
	/*recv(ns,buff,sizeof(buff),0);
	printf("Message From Client: %s",buff);
	printf("Enter Message: ");
	//fflush(stdln);
	scanf("%s",buff);
	send(ns,buff,sizeof(buff),0);*/

	while(1)
	{
		int choice = 0,i,num,x=-1;
		int odd[50],even[50],n1=0,n2=0;
		int n,j;
		
		read(ns,&choice,sizeof(choice));
		printf("Choice Selected %d\n",choice);
		if (choice==0)
		{
			break;
		}

		read(ns,&n,sizeof(n));
		recv(ns,buff,sizeof(buff),0);
		printf("Recieved Array: ");
		for(i=0;i<n;i++)
		{
			printf("%d ",buff[i]);
		}
		printf("\n");
		switch(choice)
		{
			case 1:
			//int j;
			/*for(i=0;i<n-1;i++)
			{
				for(j=0;j<n-i-1;j++)
				{
					if(buff[j]>buff[j+1])
					{
						int temp = buff[i];
						buff[i] = buff[j];
						buff[j] = temp;
					}
				}

			}
			printf("%d\n",n);
			for(i=0;i<n;i++)
			{
				printf("%d ",buff[i]);
			}*/
			insertionSort(buff,n);
			write(ns,buff,sizeof buff);
			printf("Array Sorted and sent to client\n");
			break;

			case 2:
			read(ns,&num,sizeof(int));
			for(i=0;i<n;i++)
			{
				if(buff[i] == num)
				{
					x=1;
					write(ns,&(i),sizeof(int));
					break;
				}
			}
			if(x!=1)
			{
				i=-1;
				write(ns,&i,sizeof(int));
			}
			break;

			case 3:
			for(i=0;i<n;i++)
			{
				if(buff[i]%2==0)
					even[n1++] = buff[i];
				else
					odd[n2++] = buff[i];
			}

			write(ns,&n1,sizeof(int));
			write(ns,&n2,sizeof(int));
			write(ns,even,sizeof(even));
			write(ns,odd,sizeof(odd));
			printf("Odd and Even Array Sent\n");
			break;
			

		}
		
	}
	
	close(ns);
	close(s);

}