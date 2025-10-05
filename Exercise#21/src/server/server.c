#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../mess_struct.h"
#include "../socket_func.h"
#include "../addr_and_port_const.h"
#include "server_func.h"
#include "extern.h"

int main_pid = 0;
int main_socket_fd = 0;

int main(){
    signal(SIGINT, sigint);
    main_pid = getpid();
    struct sockaddr_in server, client;
    struct in_addr addr;
    char mess[25] = "Redirect ";
    struct mess message;
    addr.s_addr = SERVER_ADDR;
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = START_PORT;

    open_socket(&main_socket_fd);
    while(1){
        memset(&message, 0, sizeof(message));
        get_mess(&main_socket_fd, &message, &client);
        if(message.udp_hdr.dest == server.sin_port){
            new_con(client);
        }
    }
    close(main_socket_fd);
}