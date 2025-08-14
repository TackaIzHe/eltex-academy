#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    struct sockaddr_un server, client;
    socklen_t sock_len_client = sizeof(client);
    int fd;
    int new_fd;
    char buff[256];
    char sa_data[25];

    strcpy(sa_data, ".Makefile");

    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, sa_data);
    
    fd = socket(AF_LOCAL,SOCK_STREAM,0);
    if(fd == -1){
        perror("Ошибка создания сокета\n");
        exit(EXIT_FAILURE);
    }
    if(bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1){
        perror("Ошибка bind\n");
        exit(EXIT_FAILURE);
    }
    
    if(listen(fd, 1) == -1){
        perror("Ошибка установки масимального количества подключения\n");
        exit(EXIT_FAILURE);
    }

    new_fd = accept(fd, (struct sockaddr*)&client, (socklen_t*)&sock_len_client);
    if(new_fd == -1){
        perror("Ошибка подключения клиента\n");
    }

    recv(new_fd, buff, 256, 0);

    printf("%s\n",buff);

    send(new_fd, "Hi!", 4, 0);
    
    close(fd);
    close(new_fd);

    unlink(".Makefile");

    exit(EXIT_SUCCESS);
}