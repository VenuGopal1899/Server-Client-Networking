// M Venu Gopal
// 17CS8064
// Server code

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
#include<ctype.h>
#include<unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<semaphore.h>
#include<signal.h>



int main()
{
	int socket_id,newsocket_id,client_address_length;
	struct sockaddr_in server_address,client_address;
	pid_t newserver;
	int flag=0;
	int personal_player_no=0;
	int i=0,x=0,j=0;

	printf("tictac toe 3x3\n");
	int segment_id1 = shmget(IPC_PRIVATE, sizeof(char)*100, S_IRUSR | S_IWUSR);
	char *buffer = (char*)shmat(segment_id1, NULL, 0);
	int segment_id2 = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
	int *player_no = (int*)shmat(segment_id2, NULL, 0);


	int seg1 =shmget(IPC_PRIVATE,sizeof(sem_t),S_IRUSR|S_IWUSR);
	sem_t *tt1 = (sem_t *)shmat(seg1,NULL,0);
	sem_init(tt1,1,1);
	int seg2 =shmget(IPC_PRIVATE,sizeof(sem_t),S_IRUSR|S_IWUSR);
	sem_t *tt2 = (sem_t *)shmat(seg2,NULL,0);
	sem_init(tt2,1,1);


	for(i=0;i<9;++i)
	{
		buffer[i]='0';
	}

	*player_no=0;

	if((socket_id=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("socket creation Error\n");
		exit(0);
	}

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=INADDR_ANY;
	server_address.sin_port=htons(6000);

	if((bind(socket_id,(struct sockaddr*)&server_address, sizeof(server_address)))<0)
	{
		printf("unable to bind \n");
		exit(0);
	}
	sem_wait(tt1);
	sem_wait(tt2);
	listen(socket_id,2);
	while(1)
	{
		client_address_length=sizeof(client_address);
		newsocket_id=accept(socket_id,(struct sockaddr*)&client_address,&client_address_length);
		*player_no=(*player_no)+1;
		if(newsocket_id<0)
		{
			printf("accept error\n");
			exit(0);
		}
		personal_player_no=*player_no;
		printf("Player %d joined\n",*player_no);
		if(*player_no==2)
			sem_post(tt1);
		if(fork()==0)
		{

			if(strcmp(buffer,"-1")==0)
			{
				label:
				send(newsocket_id,buffer,strlen(buffer)+1,0);
				*player_no=(*player_no)-1;
				x=close(newsocket_id);
				sem_post(tt1);
				sem_post(tt2);
				shmdt(buffer);
				shmdt(player_no);
				shmdt(tt1);
				shmdt(tt2);
				kill(0,SIGINT);
				exit(0);
			}
			if(personal_player_no==1)
			{
				while(1)
				{
					sem_wait(tt1);

					send(newsocket_id,buffer,strlen(buffer)+1,0);
					recv(newsocket_id,buffer,100,0);

					for(j=0;j<9;++j)
					{
						if(buffer[j]=='9')
							buffer[j]='1';
					}

					if((buffer[0]==buffer[1])&&(buffer[1]==buffer[2]))
					{
						if(buffer[0]=='1'||buffer[0]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[0]);
							goto label;
						}
					}
					if((buffer[3]==buffer[4])&&(buffer[4]==buffer[5]))
					{
						if(buffer[3]=='1'||buffer[3]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[3]);
							goto label;
						}
					}
					if((buffer[6]==buffer[7])&&(buffer[7]==buffer[8]))
					{
						if(buffer[6]=='1'||buffer[6]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[6]);
							goto label;
						}
					}
					if((buffer[0]==buffer[3])&&(buffer[3]==buffer[6]))
					{
						if(buffer[0]=='1'||buffer[0]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[0]);
							goto label;
						}
					}
					if((buffer[1]==buffer[4])&&(buffer[4]==buffer[7]))
					{
						if(buffer[1]=='1'||buffer[1]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[1]);
							goto label;
						}
					}
					if((buffer[2]==buffer[5])&&(buffer[5]==buffer[8]))
					{
						if(buffer[2]=='1'||buffer[2]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[2]);
							goto label;
						}
					}
					if((buffer[0]==buffer[4])&&(buffer[4]==buffer[8]))
					{
						if(buffer[0]=='1'||buffer[0]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[0]);
							goto label;
						}
					}
					if((buffer[2]==buffer[4])&&(buffer[4]==buffer[6]))
					{
						if(buffer[2]=='1'||buffer[2]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[2]);
							goto label;
						}
					}
					send(newsocket_id,buffer,strlen(buffer)+1,0);
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
						goto label;
					}
					flag=0;
					sem_post(tt2);
				}
			}
			else
			{
				while(1)
				{
					sem_wait(tt2);

					send(newsocket_id,buffer,strlen(buffer)+1,0);
					recv(newsocket_id,buffer,100,0);


					for(j=0;j<9;++j)
					{
						if(buffer[j]=='9')
							buffer[j]='2';
					}

					if((buffer[0]==buffer[1])&&(buffer[1]==buffer[2]))
					{
						if(buffer[0]=='1'||buffer[0]=='2')
						{
								send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[0]);
							goto label;
						}
					}
					if((buffer[3]==buffer[4])&&(buffer[4]==buffer[5]))
					{
						if(buffer[3]=='1'||buffer[3]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[3]);
							goto label;
						}
					}
					if((buffer[6]==buffer[7])&&(buffer[7]==buffer[8]))
					{
						if(buffer[6]=='1'||buffer[6]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[6]);
							goto label;
						}
					}
					if((buffer[0]==buffer[3])&&(buffer[3]==buffer[6]))
					{
						if(buffer[0]=='1'||buffer[0]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[0]);
							goto label;
						}
					}
					if((buffer[1]==buffer[4])&&(buffer[4]==buffer[7]))
					{
						if(buffer[1]=='1'||buffer[1]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[1]);
							goto label;
						}
					}
					if((buffer[2]==buffer[5])&&(buffer[5]==buffer[8]))
					{
						if(buffer[2]=='1'||buffer[2]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[2]);
							goto label;
						}
					}
					if((buffer[0]==buffer[4])&&(buffer[4]==buffer[8]))
					{
						if(buffer[0]=='1'||buffer[0]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[0]);
							goto label;
						}
					}
					if((buffer[2]==buffer[4])&&(buffer[4]==buffer[6]))
					{
						if(buffer[2]=='1'||buffer[2]=='2')
						{
							send(newsocket_id,buffer,strlen(buffer)+1,0);
							printf("\nplayer %c won\n",buffer[2]);
							goto label;
						}
					}
					send(newsocket_id,buffer,strlen(buffer)+1,0);
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
						goto label;
					}
					flag=0;
					sem_post(tt1);
				}
			}
			goto label;
		}
		close(newsocket_id);
	}
	shmdt(buffer);
	shmdt(player_no);
	shmdt(tt1);
	shmdt(tt2);
	sem_destroy(tt1);
	sem_destroy(tt2);
	shmctl(segment_id1, IPC_RMID, NULL);
	shmctl(seg1, IPC_RMID, NULL);
	shmctl(segment_id2, IPC_RMID, NULL);
	shmctl(seg2, IPC_RMID, NULL);
	return 0;
}
