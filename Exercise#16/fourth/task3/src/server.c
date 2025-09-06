#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define HANDLE_ERR(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)

#define PORT 50501

int main(){
    int fd;
    socklen_t client_len;
    char buff[256];
    struct sockaddr_in server, client;
    struct in_addr server_addr;

    server_addr.s_addr = inet_addr("192.168.0.17");

    server.sin_addr = server_addr;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    
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
    buff[1] = 'Q';
    printf("%s\n", buff);
    if(sendto(fd, buff, strlen(buff)+1, 0, (struct sockaddr*)&client, client_len) == -1){
        close(fd);
        HANDLE_ERR("recvfrom err");
    }
    close(fd);
    
    exit(EXIT_SUCCESS);
}