#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define handle_err(msg)\
    do{ perror(msg); exit(EXIT_FAILURE); }while(0)

int main(){
    int fd, client_fd;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_un serv, client;
    socklen_t client_len;

    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path, ".Makefile20");

    client_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(client_fd == -1){
        handle_err("socket2");
    }

    if( bind(client_fd,(struct sockaddr*)&client, sizeof(client)) == -1){
        handle_err("bind2");
    }

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, ".Makefile");

    if( sendto(client_fd, "Hello!", 7, 0, (struct sockaddr*)&serv, sizeof(serv)) == -1){
        handle_err("send");
    }
    
    client_len = sizeof(client);
    if( recvfrom(client_fd, buff, buff_len, 0,(struct sockaddr*)&client, &client_len) == -1){
        handle_err("recv");
    }
    printf("%s\n", buff);

    close(client_fd);

    unlink(".Makefile20");
    
    exit(EXIT_SUCCESS);
}