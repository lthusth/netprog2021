#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in saddr;
	struct hostent *host;
	unsigned short port = 8784;
	

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("Error: Creating socket failed\n");
		return -1;
	}

	if (argc < 2) {
		char str[100];
		printf("Input hostname u want to find ip addresses: ");
		scanf("%s", str);
		host = gethostbyname(str);
	}
	else {
		host = gethostbyname(argv[1]);
	}

	
	unsigned int i=0;	
	while (host->h_addr_list[i] != NULL) {
		printf( "%s\n", inet_ntoa( *(struct in_addr*)(host->h_addr_list[i])));
		i++;
	}
	printf("\n");


	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
	saddr.sin_port = htons(port);
	
	if(connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
		printf("Cannot connect\n");
		exit(-1);
	}
	return 0;
}