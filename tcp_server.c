#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
void error_handling (char *message);
int main(void){
	
	//varibles
	
	int serverSocketFd, clientSocketFd;
	struct sockaddr_in serverAddress, clientAddress;
	int clientAddressLenght;
	
	//socket creation
	serverSocketFd=socket(AF_INET,SOCK_STREAM,0);
	
		if(serverSocketFd==-1) 
		{
			printf("failed to create a socket\n");
			exit(1);
		}
		
		else {
			printf("socket : %d\n",serverSocketFd);
		}
		
	//bind
	
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons(PORT);
	
	if(bind(serverSocketFd,(struct sockaddr*)&serverAddress,sizeof(serverAddress))!=0){
		
		printf("failed to bind\n");
			exit(1);				
	}
	
	else {
		
		printf("bound\n");
	}
	
	//listening
	
		if(listen(serverSocketFd,1)!=0){
			
		printf("failed to listen \n");
		exit(1);
						
		}
		else{
			printf("listening...\n");
		}
	//accepting
	
	bzero(&clientAddress,sizeof(clientAddress));
	clientSocketFd=accept(serverSocketFd,(struct sockaddr*)&clientAddress,&clientAddressLenght);
	if(clientSocketFd==-1){
		printf("failed to accept\n");
		exit(1);	
	}
	else{
		printf("accepted\n");
	}
	//writing
	char *msg="hello world!";
	write(clientSocketFd,(char *)msg,strlen(msg));
	printf("sent : \"%s\"\n",msg);
		
	//close
	close(serverSocketFd);
		printf("server socket closed\n");
	close(clientSocketFd);
		printf("client socket closed\n");
	
}

void error_handling(char *message){
	
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
	
}
