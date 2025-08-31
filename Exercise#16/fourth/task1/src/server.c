#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define HANDLE_ERR(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

#define PORT 5050

int main(){
    int fd;
    socklen_t client_len;
    char buff[256];
    struct sockaddr_in server, client;
    struct in_addr server_addr;

    server_addr.s_addr = htonl(INADDR_LOOPBACK);

    server.sin_addr = server_addr;
    server.sin_family = AF_INET;
    server.sin_port = PORT;
    
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        HANDLE_ERR("socket err");
    }

    if(bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1){
        close(fd);
        HANDLE_ERR("bind err");
    }

    client_len = sizeof(client);
    if(recvfrom(fd, buff, 256, 0, (struct sockaddr*)&client, &client_len) == -1){
        close(fd);
        HANDLE_ERR("recvfrom err");
    }

    printf("%s\n", buff);
    close(fd);
    
    exit(EXIT_SUCCESS);
}