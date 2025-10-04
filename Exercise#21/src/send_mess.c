#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int send_mess(int* fd, char* buff, int buff_lenght, struct sockaddr_in* dest){
    sendto(*fd, buff, 46, 0, (struct sockaddr*)dest, sizeof(*dest));
}