#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>

#define BUFSIZE 256
#define PORT 50064

char Buffer[1024]={0};

void listoffiles(char* buffer)
{  
   int i=0,j=0;
   struct dirent *de;  
   DIR *dr = opendir(buffer); 
  
   if (dr == NULL)  
   { 
      printf("Could not open current directory\n" ); 
   }

   while ((de = readdir(dr)) != NULL) 
   {
	   while(de->d_name[j]!='\0')
	   {
		   Buffer[i]=de->d_name[j];
		   j++; i++;
	   }
	   j=0;
	   Buffer[i]='|';
	   i++;
           if(i>1024)
		break;
	   else
		continue;

   }
   closedir(dr);
}

int main()
{
   int sockfd,p;
   char buffer[BUFSIZE];
   struct sockaddr_in servaddr,cliaddr;

   if(( sockfd = socket(AF_INET,SOCK_DGRAM,0))<0) 
     {
        printf("error in creating server socket \n");
        exit(0);
     }
   printf("Server socket successfully created \n");

   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=INADDR_ANY;
   servaddr.sin_port = htons(PORT);

   if(bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr))<0)
   {
     printf("error in binding socket\n");
     exit(0);
   }
   printf("Binding sucessfully completed\n");
   int k,len,n;
   len=sizeof(cliaddr);
   n=recvfrom(sockfd,(char*) buffer,BUFSIZE,MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);

   buffer[n]='\0';
   printf("Directory sent by client is : %s\n",buffer);
   listoffiles(buffer);
   k=sendto(sockfd,(const char*)Buffer,strlen(Buffer),MSG_CONFIRM,(const struct sockaddr*)&cliaddr,sizeof(cliaddr));

   printf("\nList sent to client \n");

   return 0;


}
