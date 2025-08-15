#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define handle_err(msg)\
    do{ perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int fd = 0;
    char buff[256];
    int len_buff = 256;
    socklen_t client_len;
    struct sockaddr_un serv, client;

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path,".Makefile");
    
    fd = socket(AF_LOCAL,SOCK_DGRAM,0);
    if(fd == -1){
        handle_err("socket");
    }
    if(bind(fd, (struct sockaddr*)&serv, sizeof(serv)) == -1){
        handle_err("bind");
    }
    
    client_len = sizeof(client);
    if( recvfrom(fd, buff, len_buff, 0, (struct sockaddr*)&client, &client_len) == -1 ){
        perror("recv");
    }
    printf("%s\n", buff);
    
    if(sendto(fd, "Hi!", 4, 0, (struct sockaddr*)&client, sizeof(client)) == -1){
        perror("send\n");
    }
    
    close(fd);
    
    unlink(".Makefile");

    exit(EXIT_SUCCESS);
}