#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "../socket_func.h"
#include "server_func.h"
#include "../addr_and_port_const.h"

int server_port;
int client_port;
int socket_fd = 0;

int new_con(struct sockaddr_in client){
    pid_t pid = 0;
    pid = fork();
    if(pid == 0){
        struct sockaddr_in server; 
        struct sockaddr_in c;
        signal(SIGINT, sigint);
        int count = 1;
        int pid = getpid();
        int buff_lenght = 1024;
        char buff[buff_lenght];
        char mess_buff[buff_lenght];
        struct mess message;
        server.sin_addr.s_addr = SERVER_ADDR;
        server.sin_family = AF_INET;
        server.sin_port = pid + START_PORT;
        open_socket(&socket_fd);
        strcpy(mess_buff, "OK!");
        set_header(buff, buff_lenght, mess_buff, client, server);
        send_mess(&socket_fd, buff, &client);
        client_port = client.sin_port;
        server_port = server.sin_port;
        while(1){
            memset(&message, 0, sizeof(message));
            get_mess(&socket_fd,&message, &c);
            if( (message.udp_hdr.dest == server.sin_port) && (message.ip_hdr.daddr == server.sin_addr.s_addr)){
                if(strcmp(message.payload, "exit ") == 0){
                    printf("disconnect port: %d\n", message.udp_hdr.source);
                    break;
                }
                memset(mess_buff, 0, buff_lenght);
                memset(buff, 0, buff_lenght);
                
                strcpy(mess_buff, message.payload);
                
                memset(&message, 0, sizeof(message));
                char int_char[10];
                convert_int_to_char(count, int_char, 10);
                strcat(mess_buff, " ");
                strcat(mess_buff, int_char);
                set_header(buff, buff_lenght, mess_buff, c, server);
                send_mess(&socket_fd,buff,&c);
                count++;
            }
        }

        close(socket_fd);
    }else{
        return 0;
    }
}