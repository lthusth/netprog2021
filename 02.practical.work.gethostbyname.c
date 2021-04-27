#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char **argv)
{
	struct hostent *host;
	char str[100];

    if (argc < 2) {
    	printf("Input hostname u want to find ip addresses: ");
    	scanf("%s", str);
    	host = gethostbyname(str);
	}
	else {
		host = gethostbyname(argv[1]);
	}
	
	printf("Looking up....\n");

	if (host == NULL) {
		printf("Cannot find gethostbyname() \n");
	} else{

	printf("IP address:\n");
	
	unsigned int i=0;
	
	while (host->h_addr_list[i] != NULL) {
		printf( "%s\n", inet_ntoa( *(struct in_addr*)(host->h_addr_list[i])));
		i++;
	}
	printf("\n");
	
	}
}