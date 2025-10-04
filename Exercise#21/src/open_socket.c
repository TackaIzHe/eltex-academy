#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int open_socket(int* fd){
    int one = 1;
    *fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(*fd == -1){
        perror("socket err");
    }
    if( setsockopt(*fd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) == -1){
        close(*fd);
        perror("setsockopt err");
        exit(EXIT_SUCCESS);
    }
}