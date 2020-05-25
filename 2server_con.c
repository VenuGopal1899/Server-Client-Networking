#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int calculate(char expression[]) {
    char operator = '+';
    int result = 0, counter = 0, number = 0;

    for(;counter<=strlen(expression);counter++) {

        if('0' <= expression[counter] && expression[counter] <= '9') {
            number=(number*10) + (expression[counter]-'0');
        }
        else {
        	switch(operator) {
	        	case '+': result += number;
	        			  break;
	        	case '-': result -= number;
	        			  break;
	        	case '*': result *= number;
	        			  break;
	        	case '/': result /= number;
	        			  break;
	        }
	        operator = expression[counter];
	        number = 0;
        }
    }

    return result;
}

int main()
{
    int sockfd, newsockfd;
    int clilen;
    struct sockaddr_in cli_addr,serv_addr;
    int i;
    char buffer[100];

    if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("UNABLE TO CREATE SOCKET..\n");
        exit(0);
    }

    printf("Server socket created successfully..\n");
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(50064);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("UNABLE TO BIND LOCAL ADDRESS..\n");
        exit(0);
    }

    printf("Binding completed..\n");

    listen(sockfd, 5);

    while(1) {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newsockfd < 0) {
            printf("UNABLE TO ACCEPT..\n");
            exit(0);
        } 

        if(fork() == 0) {
        	close(sockfd);

        	for(i=0; i < 100; i++) buffer[i] = '\0';

	        while(1) {
		        recv(newsockfd,buffer,100,0);

		        if(buffer[0]=='-'&&buffer[1]=='1'&&buffer[2]=='\0')
		        	break;

		        printf("Received arithmetic expression is : %s \n",buffer);
		        
			    int answer = calculate(buffer), counter = 0, n = answer;

		        if(n==0) {
		            counter = 1;
		        }
		        else {
		        	while(n > 0) {
			            counter++;
			            n/=10;
		        	}
		        }

		        for(i = 0; i < 100; i++) buffer[i] = '\0';

			    for(i = counter-1; i >= 0; i--) {
				    buffer[i] = ('0' + answer%10);
				    answer/=10;		
			    }
		        
			    printf("%s is the answer in string\n", buffer);
		        send(newsockfd, buffer, strlen(buffer)+1, 0);
	    	}

	    	close(newsockfd);
	    	exit(0);
        }
        
    	close(newsockfd);
	}

	return 0;
}
