#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(){
    int fd = 0;
    struct sockaddr_un serv, client;
    fd = socket(AF_LOCAL,SOCK_DGRAM,0);

    exit(EXIT_SUCCESS);
}