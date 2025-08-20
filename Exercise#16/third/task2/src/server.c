#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int fd;

#define PORT 5050
#define handle_err(msg)\
    do { close(fd); perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    struct sockaddr_in client;
    struct in_addr addr;
    addr.s_addr = inet_addr("224.0.0.1");
    client.sin_addr = addr;
    client.sin_family = AF_INET;
    client.sin_port = PORT;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        handle_err("socket err");
    }
    for(int i=0; i<10;i++){
        if( sendto(fd, "123", 4, 0, (struct sockaddr*)&client, sizeof(client)) == -1 ){
            handle_err("sendto err");
        }
    }
    close(fd);
    exit(EXIT_SUCCESS);
}