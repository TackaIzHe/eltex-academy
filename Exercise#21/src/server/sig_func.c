#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../addr_and_port_const.h"
#include "../mess_struct.h"
#include "../socket_func.h"

extern int main_socket_fd;
extern int main_pid;
extern int server_port;
extern int client_port;

void sigint(int){
    if(main_pid != getpid()){
        extern int socket_fd;
        char buff[1024];
        char mess[1024];
        int buff_lenght = 1024;
        memset(buff, 0, buff_lenght);
        memset(mess, 0, buff_lenght);
        strcpy(mess, "exit");
        
        struct sockaddr_in server, client;
        server.sin_addr.s_addr = SERVER_ADDR;
        server.sin_family = AF_INET;
        server.sin_port = server_port;

        client.sin_addr.s_addr = SERVER_ADDR;
        client.sin_family= AF_INET;
        client.sin_port = client_port;

        set_header(buff, buff_lenght, mess, client, server);
        send_mess(&socket_fd, buff, &client);
        close(socket_fd);
        exit(EXIT_SUCCESS);
    }{
        close(main_socket_fd);
        exit(EXIT_SUCCESS);
    }
}