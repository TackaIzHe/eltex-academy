#include <signal.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../socket_func.h"

int socket_fd = 0;
int pid = 0;

void sigint(int){
    /// ОТПРОВЛЯТЬ серверу СООБЩЕНИЕ О ВЫКЛЮЧЕНИИ клиента
    close(socket_fd);
    exit(EXIT_SUCCESS);
}

int main(){
    signal(SIGINT, sigint);
    pid = getpid();
    struct sockaddr_in server, client;
    struct in_addr addr;
    char buff[1024];
    char* ptr = (void*)&buff;
    int buff_lenght = 1024;
    char mess[15] = "Hello World!";
    addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = htons(50001);

    client.sin_addr = addr;
    client.sin_family = AF_INET;
    client.sin_port = htons(50002);

    open_socket(&socket_fd);
 
    set_header(&ptr,buff_lenght, mess, server, client);
    send_mess(&socket_fd, ptr, buff_lenght, &server);
    
    
}