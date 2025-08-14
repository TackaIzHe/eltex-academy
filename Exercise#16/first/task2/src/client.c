#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define handle_err(msg)\
    do {perror(msg);exit(EXIT_FAILURE); } while(0)

int main(){
    int fd;
    char buff[256];
    struct sockaddr_un server;

    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path,".Makefile");

    fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(fd == -1){
        handle_err("socket\n");
    }
    if( connect(fd, (struct sockaddr*)&server,sizeof(server)) == -1){
        handle_err("con\n");
    }

    send(fd, "Hello!",7,0);

    recv(fd, buff, 256, 0);

    printf("%s\n",buff);

    close(fd);

    exit(EXIT_SUCCESS);

}