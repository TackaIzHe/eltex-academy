#include "mess_struct.h"
#include <sys/socket.h>
#include <stdio.h>

int get_mess(int* fd, struct mess* message, struct sockaddr_in* client){
    recv(*fd, message, sizeof(struct mess), 0);
    client->sin_addr.s_addr = message->ip_hdr.saddr;
    client->sin_family = AF_INET;
    client->sin_port = message->udp_hdr.source;
}