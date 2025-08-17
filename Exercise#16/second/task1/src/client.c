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
    int new_fd;
    int new_port;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in server;
    struct in_addr addr;
    addr.s_addr = htonl(INADDR_LOOPBACK);
    
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
    
    if( recv(fd, &new_port, 4, 0) == -1 ){
        handle_err("recv");
    }
    close(fd);

    server.sin_port = new_port;

    
    new_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        handle_err("socond socket");
    }
    
    if(connect(new_fd, (struct sockaddr*)&server, sizeof(server)) == -1){
        handle_err("second connect");
    }

    if( send(new_fd, "time", 5, 0) == -1 ){
        handle_err("second recv");
    }

    if( recv(new_fd, buff, buff_len, 0) == -1 ){
        handle_err("second recv");
    }

    printf("%s\n", buff);
        
    close(fd);
    exit(EXIT_SUCCESS);
}