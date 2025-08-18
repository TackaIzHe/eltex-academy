#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 2520
#define CLIENT_PORT 3530
#define handle_err(msg)\
    do{perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int fd;
    int new_port;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in server, client;
    socklen_t client_len;
    struct in_addr addr;
    addr.s_addr = htonl(INADDR_LOOPBACK);
    
    client.sin_addr = addr;
    client.sin_family = AF_INET;
    client.sin_port = CLIENT_PORT;

    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = PORT;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        handle_err("socket");
    }
    if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1){
        handle_err("bind err");
    }
    
    if(sendto(fd, "con", 4, 0, (struct sockaddr*)&server, sizeof(server)) == -1){
        handle_err("sendto err");
    }
    client_len = sizeof(client);
    if(recvfrom(fd, &new_port, 4, 0, (struct sockaddr*)&client, &client_len) == -1){
        handle_err("sendto err");
    }
    server.sin_port = new_port;

    if(sendto(fd, "con", 4, 0, (struct sockaddr*)&server, sizeof(server)) == -1){
        handle_err("sendto err");
    }

    while(1){
        strcpy(buff,"");
        scanf("%s",buff);
        if( sendto(fd, buff, strlen(buff)+1, 0,(struct sockaddr*)&server, sizeof(server)) == -1 ){
            close(fd);
            handle_err("second recv");
        }
        if(strcmp(buff,"exit") == 0){
           close(fd);
           break; 
        }
        client_len = sizeof(client);
     
        if( recvfrom(fd, buff, buff_len, 0, (struct sockaddr*)&client, &client_len) == -1 ){
            close(fd);
            handle_err("second recv");
        }
        printf("%s\n", buff);
        
    }

    exit(EXIT_SUCCESS);
}