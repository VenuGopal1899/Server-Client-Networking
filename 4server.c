#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 5000
#define MAXLINE 1024

char * Palindrome(char * buffer)
{
    int p,q,l;
    l = strlen(buffer);
    char* str;
    str=(char *)malloc(sizeof(char )*l);
    for(p=0;p<l;p++)
    {
        *(str+p)=buffer[p];
	}

    for(q=0;q<l/2;q++)
    {
        if(str[q]!=str[l-q-1])
        {
            puts("Nope");
            return("Nope");
        }
    }
    puts("Yup");
    return("Yup");
}

int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

int main()
{
	int listenfd, connfd, udpfd, nready, maxfdp1;
	char buffer[MAXLINE];
	pid_t childpid;
	fd_set rset;
	ssize_t n;
	socklen_t len;
	const int on = 1;
	struct sockaddr_in cliaddr, servaddr;
	void sig_chld(int);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, 10);

	udpfd = socket(AF_INET, SOCK_DGRAM, 0);

	bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	FD_ZERO(&rset);

	maxfdp1 = max(listenfd, udpfd) + 1;
	while(1)
    {

		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);

		nready = select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset))
        {
			len = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
			if ((childpid = fork()) == 0)
            {
				close(listenfd);
				bzero(buffer, sizeof(buffer));
				printf("\nMessage From TCP client: ");
				read(connfd, buffer, sizeof(buffer));
				puts(buffer);
                char * message = Palindrome(buffer);
				write(connfd, (const char*)message, sizeof(message));
				close(connfd);
				exit(0);
			}
			close(connfd);
		}

		if (FD_ISSET(udpfd, &rset))
        {
			len = sizeof(cliaddr);
			bzero(buffer, sizeof(buffer));
			printf("\nMessage from UDP client: ");
			n = recvfrom(udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
			puts(buffer);
            char * message = Palindrome(buffer);
			sendto(udpfd, (const char*)message, sizeof(message), 0,(struct sockaddr*)&cliaddr, sizeof(cliaddr));
		}
	}
}
