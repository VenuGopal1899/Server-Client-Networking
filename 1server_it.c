#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int calculate(char exp[])
{
    char op='+';
    int res=0,q=0,a=0;
    for(;q<=strlen(exp);q++)
    {
        if('0' <= exp[q] && exp[q] <= '9')
        {
            a=(a*10) + (exp[q]-'0');
        }
        else
        {
            if(op == '+')
				res += a;
			else if(op == '-')
				res -= a;
			else if(op == '*')
				res *= a;
			else if(op == '/')
				res /= a;
			op = exp[q];
            a=0;
        }
    }
    return res;
}

int main()
{
    int sockfd,newsockfd;
    int clilen;
    struct sockaddr_in cli_addr,serv_addr;
    int i;
    char buffer[100];

    if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("UNABLE TO CREATE SOCKET..\n");
        exit(0);
    }
    printf("Server socket created successfully..\n");
    

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(50064);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("UNABLE TO BIND LOCAL ADDRESS..\n");
        exit(0);
    }
    printf("Binding completed..\n");
    

    listen(sockfd, 5);

    while(1)
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newsockfd < 0)
        {
            printf("UNABLE TO ACCEPT..\n");
            exit(0);
        } 

        for(i=0; i < 100; i++) buffer[i] = '\0';

        while(1) 
        {
            recv(newsockfd,buffer,100,0);
            if(buffer[0]=='-' && buffer[1]=='1' && buffer[2]=='\0')
            {
                printf("Server is closed..\n");
                close(newsockfd);
            }
            printf("Received arithmetic expression is : %s \n",buffer);
        
            int ans = calculate(buffer);
            int c = 0;
            int n = ans;
            if(n==0)
            {
                c=1;
            }
            
            while(n > 0)
            {
                c++;
                n/=10;
            }

            for(i=0; i < 100; i++) buffer[i] = '\0';

            for(i=c-1;i>=0;i--)
            {
                buffer[i] = ('0' + ans%10);
                ans/=10;		
            }
            
            printf("%s is the answer in string\n", buffer);
            send(newsockfd,buffer,strlen(buffer) +1,0);
        }
    }

}
