#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX 1000

int main(int argc, char const *argv[])
{
	int clen, clientfd, sockfd, n, i;
	int last_fd, new_fd;
	struct sockaddr_in saddr, caddr;
	unsigned short port = 8784;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("Error: Creating socket failed\n");
		return -1;
	}

	last_fd = sockfd;
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);
	
	if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) 
	{
		printf("Error: Binding failed\n");
		return -1;
	}else{
		printf("Successfully binded\n");
	}

	printf("Loading on port...%d \n", port);
	if (listen(sockfd, 10) < 0) 
	{
		printf("Error: Listening failed\n");
		return -1;
	}else{
		printf("Server listening.....\n");
	}

	clen = sizeof(caddr);
	clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen);
	if (clientfd < 0) 
	{
		printf("Error: Accepting connection failed\n");
		return -1;
	}else{
		printf("Client connected success\n");
	}
	new_fd = clientfd;


	fcntl(last_fd, F_SETFL, O_NONBLOCK);
	fcntl(new_fd, F_SETFL, O_NONBLOCK);

	// while(1){
	// 	char mess[MAX];
	// 	static const char delim = '\n';

	// 	bzero(mess, MAX);
	// 	n = recv(clientfd, mess, sizeof(mess), 0);

	// 	if (n < 0 || mess[n-1] == delim){
	// 		printf("ERROR reading from socket\n");
	// 	}

	// 	printf("Client send: %s\n",mess);
		

	// 	// if(mess[0]  == '\n'){
	// 	// 	printf("Error\n");
	// 	// }

	// 	bzero(mess, MAX);
	// 	printf("Server sending back: \n");
	// 	fgets(mess, MAX, stdin);

	// 	n = send(clientfd, mess, sizeof(mess), 0);
	// 	if (n < 0){
	// 		printf("ERROR writing from socket\n");
	// 	}

	// 	if (strncmp("dc", mess, 2) == 0);
	// 	{
	// 		printf("shutting down server now...\n");
	// 		shutdown(sockfd, 2);
	// 		exit(0);
	// 	}
	// }
	while (1){
		for (i = sockfd; i <= last_fd; i++){
			char mess[MAX];
			if (i = sockfd){
				clen = sizeof(caddr);
				if((new_fd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0 ){
					printf("Error accept\n");
				}
				printf("Server got connection from %s\n", inet_ntoa(caddr.sin_addr));
				fcntl(new_fd, F_SETFL, O_NONBLOCK);
				last_fd = new_fd;
			}
			else{
				bzero(mess, MAX);
				n = recv(new_fd, mess, sizeof(mess), 0);
				if (n < 0){
					printf("Error receive nonblocking\n");
				}
				printf("client sent: %s\n",mess);
				
				bzero(mess, MAX);
				n = send(new_fd, mess, sizeof(mess), 0);
				if (n<0){
					printf("Error writing");
				}
			}

		}
	}
	return 0;
}

