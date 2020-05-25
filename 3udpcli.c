#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 256
#define PORT 50064

int main()
{
   int sockfd;
   char buffer[BUFSIZE];
   char Buffer[1024]={0};
   printf("Enter path of directory : ");
   scanf("%s",buffer);
   
   struct sockaddr_in servaddr;
   
   if(( sockfd = socket(AF_INET,SOCK_DGRAM,0))<0) 
     {
        printf("Error in creating client socket \n");
        exit(0);
     }

    memset(&servaddr,0,sizeof(servaddr));
    printf("\nSuccessfully client socket created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    int len,i,j;
    sendto(sockfd,(const char*)buffer,strlen(buffer),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
    printf("Buffer sent to server\n\n");
    len=sizeof(servaddr);
    i=recvfrom(sockfd,(char *)Buffer,1024,0,(struct sockaddr *)&servaddr,&len);
    Buffer[i]='\0';
    printf("List of files and folders in given directory :\n\n%s|\n\n",Buffer);
     
    close(sockfd);
    return 0;
}
