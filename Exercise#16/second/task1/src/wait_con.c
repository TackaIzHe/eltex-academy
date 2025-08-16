#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 2025
#define handle_err(msg)\
    do{perror(msg); exit(EXIT_FAILURE);}while(0)

void* wait_con(void*){
    int fd;
    int client_fd;
    int id = PORT + 1;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);
    struct in_addr addr;
    addr.s_addr = 127;
    
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = PORT;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        handle_err("socket");
    }

    if(bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1){
        handle_err("bind");
    }

    if(listen(fd, 10) == -1){
        handle_err("listen");
    }
    
    while(1){

        client_fd = accept(fd, (struct sockaddr*)&client, &client_len);
        if(client_fd == -1){
            handle_err("accept");
        }
        
        if( send(client_fd, &id, 4, 0) == -1){
            handle_err("send");
        }
        id++;
    }

    close(client_fd);
    close(fd);

    exit(EXIT_SUCCESS);
   
}