#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "mess_struct.h"

int send_mess(int* fd, char* buff, struct sockaddr_in* dest){
    struct mess* message = (struct mess*)buff;
    sendto(*fd, message, sizeof(message->ip_hdr) + sizeof(message->udp_hdr) + strlen(message->payload)+1, 0, (struct sockaddr*)dest, sizeof(*dest));
}