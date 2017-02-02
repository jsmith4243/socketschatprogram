#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdio.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{

	printf("Chat Client\n\n");
	
	
	
	
	
	
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[500];
	
	char bufferResponse[500];
	
	char clientUsername[500];
	
	char serverUsername[500];
	
	if (argc < 3) {
		fprintf(stderr, "please use %s hostname port\n", argv[0]);
		exit(0);
	}
	
	portno = atoi(argv[2]);
	
	 /* Create a socket point */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
	{
		error("ERROR opening socket");
		exit(1);
		
	}
	
	
	
	
	server = gethostbyname(argv[1]);
	if (server == NULL) 
	{
	
		fprintf(stderr, "ERROR, host doesnt exist\n");
		exit(0);
	}
	
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,  server->h_length);
	serv_addr.sin_port = htons(portno);
	
	
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
	{
		perror("ERROR in connecting");
		exit(1);
	}
		
	
		
	
	
	printf("Please enter your username: ");
	
	bzero(clientUsername, 500);
	fgets(clientUsername, 499, stdin);
	
	
	//printf("Your username is: %s", clientUsername);
	printf("\n");
	n = write(sockfd, clientUsername, strlen(clientUsername));
	if (n < 0)
		//error("ERROR writing to socket");
		

	
	bzero(serverUsername, 500);
		
	n = read(sockfd, serverUsername, 499);
	if (n < 0)
		error("ERROR reading from socket");
	//printf("Server username: %s\n",serverUsername);
	
				
	char *pos;
	if ((pos=strchr(serverUsername, '\n')) != NULL)
    	*pos = '\0';
	
	
		
	
	
	
	
	
	
	
		
	while(1)
	{
		
		printf("Please enter the message: ");
		
		bzero(buffer, 500);
		fgets(buffer, 499, stdin); 
		
		if (strcmp(buffer, "\\quit\n")==0)
		{
		
			break;
		
		}
		
		
		if ((pos=strchr(clientUsername, '\n')) != NULL)
    		*pos = '\0';
		//buffer[strlen(clientUsername)] = '\0';
		printf("%s: %s", clientUsername, buffer);
		
		buffer[strlen(buffer)] = '\0';
		n = write(sockfd, buffer, strlen(buffer));
		
		if (n < 0)
			error("ERROR writing to socket");
		
			
		
		

	
		
		bzero(bufferResponse, 500);
		
		n = read(sockfd, bufferResponse, 499);
		if (n < 0)
			error("ERROR reading from socket");
			
	
			
		printf("%s: %s",serverUsername, bufferResponse);
		
	}
	
	
	
		/*
		
	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if (n < 0)
		error("ERROR reading from socket");
	printf("%s\n",buffer);
	
	
	
	*/
	close(sockfd);
	
	return 0;
	
	
}
	
	
	

