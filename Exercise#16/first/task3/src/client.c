#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 2025
#define CLIENT_PORT 3025
#define handle_err(msg)\
    do{perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int fd;
    char buff[256];
    int buff_len = 256;
    socklen_t client_len;
    struct sockaddr_in server, client;
    struct in_addr addr;
    addr.s_addr = 127;
    server.sin_family = AF_INET;
    server.sin_port = PORT; 
    server.sin_addr = addr;

    client.sin_addr = addr;
    client.sin_family = AF_INET;
    client.sin_port = CLIENT_PORT;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        handle_err("socket");
    }
    if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1){
        handle_err("bind");
    }

    if( sendto(fd,"Hello!", 7, 0, (struct sockaddr*)&server, sizeof(server)) == -1){
        handle_err("sendto");
    }

    client_len = sizeof(client_len);
    if( recvfrom(fd,buff, buff_len, 0, (struct sockaddr*)&client, &client_len) == -1){
        handle_err("sendto");
    }
    printf("%s\n", buff);
    close(fd);

    exit(EXIT_SUCCESS);
}