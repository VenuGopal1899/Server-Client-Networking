// M Venu Gopal
// 17CS8064
// Client code

/*

Steps to run the code :

1.In 1st terminal, compile and run the server code with commands : gcc Server_TTT_CS64.c -o server -lpthread	&&	  ./server
2.In 2nd terminal, compile and run the client code with commands : gcc Client_TTT_CS64.c -o client -lpthread	&&	  ./client
3.In 3rd terminal, Compile and run the client code with commands : gcc Client_TTT_CS64.c -o client -lpthread	&&	  ./client

2nd terminal -- PLAYER 1
3rd terminal -- PLAYER 2

BY ENTERING VALID POSITIONS, PLAYERS CAN PLAY TIC-TAC-TOE

*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
	int socket_id;
	struct sockaddr_in server_address;

	int i=0,j=0,k=0;
	char buffer[100];
	int position=0;
	int flag=0;
	if((socket_id=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error\n");
		exit(0);
	}

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(6000);

	if((connect(socket_id,(struct sockaddr*)&server_address, sizeof(server_address)))<0)
	{
		printf("unable to connect\n");
		exit(0);
	}

	for(i=0;i<100;++i)buffer[i]='\0';
	while(strcmp("-1",buffer)!=0)
	{
		recv(socket_id,buffer,100,0);
		//printf("\nrecived %s\n",buffer);
		if(strcmp(buffer,"-1")==0)
			continue;
		printf("------------------------------------------------\n");
		for(j=0;j<3;++j)
		{
			printf("|");
			for(k=0;k<3;++k)
			{
				printf("\t%c\t|",buffer[j*3+k]);
			}
			printf("\n");
			//	|	y	|	y	|	y	|
			printf("------------------------------------------------\n");

		}



		if((buffer[0]==buffer[1])&&(buffer[1]==buffer[2]))
		{
			if(buffer[0]=='1'||buffer[0]=='2')
			{
				printf("\nplayer %c won\n",buffer[0]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[3]==buffer[4])&&(buffer[4]==buffer[5]))
		{
			if(buffer[3]=='1'||buffer[3]=='2')
			{
				printf("\nplayer %c won\n",buffer[3]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[6]==buffer[7])&&(buffer[7]==buffer[8]))
		{
			if(buffer[6]=='1'||buffer[6]=='2')
			{
				printf("\nplayer %c won\n",buffer[6]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[0]==buffer[3])&&(buffer[3]==buffer[6]))
		{
			if(buffer[0]=='1'||buffer[0]=='2')
			{
				printf("\nplayer %c won\n",buffer[0]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[1]==buffer[4])&&(buffer[4]==buffer[7]))
		{
			if(buffer[1]=='1'||buffer[1]=='2')
			{
				printf("\nplayer %c won\n",buffer[1]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[2]==buffer[5])&&(buffer[5]==buffer[8]))
		{
			if(buffer[2]=='1'||buffer[2]=='2')
			{
				printf("\nplayer %c won\n",buffer[2]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[0]==buffer[4])&&(buffer[4]==buffer[8]))
		{
			if(buffer[0]=='1'||buffer[0]=='2')
			{
				printf("\nplayer %c won\n",buffer[0]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[2]==buffer[4])&&(buffer[4]==buffer[6]))
		{
			if(buffer[2]=='1'||buffer[2]=='2')
			{
				printf("\nplayer %c won\n",buffer[2]);
				strcpy(buffer,"-1");
				continue;
			}
		}




		printf("available positions are as follows :- ");
		for(j=0;j<9;++j)
		{
			if(buffer[j]=='0')
			{
				flag=1;
				printf("%d,",j+1);
			}
		}
		if(flag==0)
		{
			printf("\ndraw\n");
			strcpy(buffer,"-1");
			break;
		}
		flag=0;
		printf("\nenter the position - ");
		scanf("%d",&position);
		while(buffer[position-1]!='0')
		{
			printf("\nenter valid position - ");
			scanf("%d",&position);
		}
		buffer[position-1]='9';
		send(socket_id, buffer,strlen(buffer)+1,0);
		recv(socket_id,buffer,100,0);

		if((buffer[0]==buffer[1])&&(buffer[1]==buffer[2]))
		{
			if(buffer[0]=='1'||buffer[0]=='2')
			{
				printf("\nplayer %c won\n",buffer[0]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[3]==buffer[4])&&(buffer[4]==buffer[5]))
		{
			if(buffer[3]=='1'||buffer[3]=='2')
			{
				printf("\nplayer %c won\n",buffer[3]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[6]==buffer[7])&&(buffer[7]==buffer[8]))
		{
			if(buffer[6]=='1'||buffer[6]=='2')
			{
				printf("\nplayer %c won\n",buffer[6]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[0]==buffer[3])&&(buffer[3]==buffer[6]))
		{
			if(buffer[0]=='1'||buffer[0]=='2')
			{
				printf("\nplayer %c won\n",buffer[0]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[1]==buffer[4])&&(buffer[4]==buffer[7]))
		{
			if(buffer[1]=='1'||buffer[1]=='2')
			{
				printf("\nplayer %c won\n",buffer[1]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[2]==buffer[5])&&(buffer[5]==buffer[8]))
		{
			if(buffer[2]=='1'||buffer[2]=='2')
			{
				printf("\nplayer %c won\n",buffer[2]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[0]==buffer[4])&&(buffer[4]==buffer[8]))
		{
			if(buffer[0]=='1'||buffer[0]=='2')
			{
				printf("\nplayer %c won\n",buffer[0]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		if((buffer[2]==buffer[4])&&(buffer[4]==buffer[6]))
		{
			if(buffer[2]=='1'||buffer[2]=='2')
			{
				printf("\nplayer %c won\n",buffer[2]);
				strcpy(buffer,"-1");
				continue;
			}
		}
		for(j=0;j<9;++j)
		{
			if(buffer[j]=='0')
			{
				flag=1;
			}
		}
		if(flag==0)
		{
			printf("\ndraw\n");
			strcpy(buffer,"-1");
			break;
		}
		flag=0;
	}
	close(socket_id);
	return 0;
}
