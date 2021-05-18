#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 1000

int main(int argc, char const *argv[])
{
    int clen, clientfd, sockfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error: Creating socket failed\n");
        return -1;
    }
    
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    
    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) 
    {
        printf("Error: Binding failed\n");
        return -1;
    }

    printf("Loading on port...%d \n", port);
    if (listen(sockfd, 10) < 0) 
    {
        printf("Error: Listening failed\n");
        return -1;
    }


    clen = sizeof(caddr);
    clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen);
    if (clientfd < 0) 
    {
        printf("Error: Accepting connection failed\n");
        return -1;
    }

    printf("Client connected success\n");

    

    while(1){
        char mess[MAX];
        bzero(mess, MAX);
            
        printf("Client: ");
        recv(clientfd, mess, sizeof(mess), 0);
        printf("%s\n", mess);

        printf("Server: ");
        fgets(mess, MAX, stdin);
        send(clientfd, mess, sizeof(mess), 0);

        if (strncmp("exit", mess, 4) == 0){
            printf("server exit...\n");
            break;
            }
        }

    return 0;

}

