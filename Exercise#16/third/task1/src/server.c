#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int fd;

#define CLIENT_PORT 5050
#define handle_err(msg)\
    do{ close(fd); perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int flag = 1;
    struct in_addr addr;
    struct sockaddr_in client;

    addr.s_addr = htonl(INADDR_BROADCAST);

    client.sin_family = AF_INET;
    client.sin_addr = addr;
    client.sin_port = CLIENT_PORT;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        handle_err("socket");
    }

    if( setsockopt(fd, SOL_SOCKET,SO_BROADCAST, &flag, sizeof(flag)) == -1){
        handle_err("setsockopt err");
    }
    for(int i=0;i<10;i++){
        if( sendto(fd, "123", 4, 0, (struct sockaddr*)&client, sizeof(client)) == -1){
            handle_err("sendto err");
        }
    }
    close(fd);
    exit(EXIT_SUCCESS);
}