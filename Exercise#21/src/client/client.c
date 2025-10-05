#include <signal.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../socket_func.h"
#include "../addr_and_port_const.h"

int server_port = 0;
int client_port = 0;

int socket_fd = 0;
int pid = 0;

void sigint(int){
    if(server_port != 0 && client_port != 0){

        char buff[1024];
        char msg[10];
        struct sockaddr_in server, client;
        server.sin_addr.s_addr = SERVER_ADDR;
        server.sin_family = AF_INET;
        server.sin_port = server_port;
        
        client.sin_addr.s_addr = SERVER_ADDR;
        client.sin_family = AF_INET;
        client.sin_port = client_port;

        memset(buff, 0, 1024);
        memset(msg, 0, 10);
        strcpy(msg, "exit");
        
        set_header(buff, 1024, msg, server, client);
        send_mess(&socket_fd, buff, &server);
    }
    close(socket_fd);
    exit(EXIT_SUCCESS);
}

int main(){
    signal(SIGINT, sigint);
    pid = getpid();
    struct sockaddr_in server, client;
    struct in_addr addr;
    char buff[1024];
    int buff_lenght = 1024;
    memset(buff, 0, buff_lenght);
    char mess[1024] = "Connect";
    struct mess message;
    addr.s_addr = SERVER_ADDR;
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = START_PORT;

    client.sin_addr = addr;
    client.sin_family = AF_INET;
    client.sin_port = START_PORT + pid;

    open_socket(&socket_fd);
 
    set_header(buff,buff_lenght, mess, server, client);
    send_mess(&socket_fd, buff, &server);

    while(1){
        get_mess(&socket_fd, &message, &server);
        if(message.udp_hdr.dest == client.sin_port){
            if(strcmp(message.payload, "OK!") == 0)
            {
                client_port = client.sin_port;
                server_port = server.sin_port;
                break;
            }
            close(socket_fd);
            exit(EXIT_FAILURE);    
        }
        
    } 

    int fork_pid = fork();
    if(fork_pid == 0){
        struct sockaddr_in s;
        int socket_fd =0;
        struct mess message;
        open_socket(&socket_fd);
        while(1){
            get_mess(&socket_fd,&message, &s);
            if((message.udp_hdr.dest == client.sin_port) && (message.ip_hdr.daddr == client.sin_addr.s_addr) && (strcmp(message.payload, "exit ") == 0)){
                close(socket_fd);
                printf("Server stop\n");
                kill(getppid(), 2);
                return 0;
            }
        }
    }

    while(1){
        memset(buff, 0, buff_lenght);
        memset(mess, 0, buff_lenght);
        memset(&message, 0, sizeof(message));
        scanf("%1024s",mess);
        set_header(buff,buff_lenght, mess, server, client);
        send_mess(&socket_fd, buff, &server);
        if(strcmp(mess, "exit ") == 0){
            break;
        }
        while(1){
            get_mess(&socket_fd,&message, &server);
            if((message.udp_hdr.dest == client.sin_port) && (message.ip_hdr.daddr == client.sin_addr.s_addr)){
                if(strcmp(message.payload, "exit ") == 0){
                    break;
                }
                printf("%s\n", message.payload);
                break;
            }
        }
    }
    close(socket_fd);
    
}