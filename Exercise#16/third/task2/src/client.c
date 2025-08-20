#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int fd;

#define PORT 5050
#define handle_err(msg)\
    do {close(fd); perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in client;
    struct in_addr addr;
    struct in_addr local_addr;
    struct ip_mreqn mreqn;
    
    addr.s_addr = inet_addr("224.0.0.1");
    local_addr.s_addr = htonl(INADDR_ANY);
    mreqn.imr_multiaddr = addr;
    mreqn.imr_address = local_addr;
    mreqn.imr_ifindex = 0;

    client.sin_addr = local_addr;
    client.sin_family = AF_INET;
    client.sin_port = PORT;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        handle_err("socket err");
    }
    if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreqn, sizeof(mreqn)) == -1){
        handle_err("setsockopt err");
    }
    if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1){
        handle_err("bind err");
    }
    for(int i=0;i<10;i++){
        if( recvfrom(fd, buff, buff_len, 0, 0, 0) == -1){
            handle_err("recvfrom err");
        }
        printf("%s\n",buff);
    }
    close(fd);

    exit(EXIT_SUCCESS);
}