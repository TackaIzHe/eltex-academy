#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 2025
#define handle_err(msg)\
    do{perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int fd;
    int id;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in server;
    struct in_addr addr;
    addr.s_addr = 127;
    
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = PORT;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        handle_err("socket");
    }

    if(connect(fd, (struct sockaddr*)&server, sizeof(server)) == -1){
        handle_err("connect");
    }

    // if( send(fd, "Hello!", 7, 0) == -1){
    //     handle_err("send");
    // }

    if( recv(fd, &id, buff_len, 0) == -1 ){
        handle_err("recv");
    }

    printf("%d\n", id);

    close(fd);

    exit(EXIT_SUCCESS);
}