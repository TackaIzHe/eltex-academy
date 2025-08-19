#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>

int fd;

#define CLIENT_PORT 5050
#define handle_err(msg)\
    do{ close(fd); perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int flag = 1;
    char buff[256];
    int buff_len = 256;
    struct in_addr addr;
    struct sockaddr_in client;
    
    addr.s_addr = htonl(INADDR_BROADCAST);
    client.sin_addr = addr;
    client.sin_family = AF_INET;
    client.sin_port = CLIENT_PORT;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        handle_err("socket");
    }
    if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1){
        handle_err("setsockopt err");
    }
    if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1){
        handle_err("bind");
    }
    for(int i=0;i<10;i++){
        if( recvfrom(fd, buff, buff_len,0, 0, 0) == -1){
            handle_err("recvfrom err");
        }
        printf("%s\n", buff);
    }
    close(fd);

    exit(EXIT_SUCCESS);
}