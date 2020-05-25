#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h> 
#include<errno.h>
#include<string.h>
#include <arpa/inet.h>
int main()
{
    int sockfd;
    struct sockaddr_in serv_addr;
    int i;
    int con;
    char buffer[100];

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("ERROR IN CREATING SOCKET ...\n");
        exit(0);
    }
    printf("Client socket created successfully..\n");
    
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(50064);
    
    int errnum;
    con=connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(con < 0)
    {
        printf("UNABLE TO CONNECT TO SERVER...\n");
        exit(0);
    }
    printf("Connected to socket successfully..\n");

    while(1)
    {
        for(i=0;i<100;i++)
        {
            buffer[i]='\0';
        }

        printf("Enter arithmetic expression : ");
        scanf("%s",buffer);
        if(buffer[0]=='-' && buffer[1]=='1' && buffer[2]=='\0')
        {
            printf("Client is closed..\n");
            break;
        }

        send(sockfd, buffer, strlen(buffer)+1,0);

        for(i=0;i<100;i++)
        {
            buffer[i]='\0';
        }

        recv(sockfd, buffer, 100, 0);
        printf("Result sent by server is : %s \n\n",buffer);
    }

    close(sockfd);
}