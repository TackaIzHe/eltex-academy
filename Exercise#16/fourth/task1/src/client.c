#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <string.h>

#define HANDLE_ERR(msg) \
    do {perror(msg); exit(EXIT_FAILURE); } while(0)

#define SERVER_PORT 5050
#define CLIENT_PORT 5353

unsigned short checksum(unsigned short *buf, int len) {
    unsigned long sum = 0;
    while (len > 1) {
        sum += *buf++;
        len -= 2;
    }
    if (len == 1) {
        sum += *(unsigned char*)buf;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

int main(){
    int fd;
    char buff[256];
    struct sockaddr_in server, client;
    socklen_t server_len;
    struct in_addr server_addr;
    struct udphdr hdr;
    char *data = buff + sizeof(hdr);
    
    hdr.source = CLIENT_PORT;
    hdr.dest = SERVER_PORT;
    hdr.len = htons(sizeof(struct udphdr) + 4);
    

    server_addr.s_addr = htonl(INADDR_LOOPBACK);

    server.sin_addr = server_addr;
    server.sin_family = AF_INET;
    server.sin_port = SERVER_PORT;

    client.sin_addr = server_addr;
    client.sin_family = AF_INET;
    client.sin_port = CLIENT_PORT;
    
    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd == -1){
        HANDLE_ERR("socket err");
    }
    
    if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1){
        close(fd);
        HANDLE_ERR("bind err");
    }

    strcpy(buff, "");
    memcpy(buff, &hdr, sizeof(hdr));
    strcpy(data , "HI!");
    hdr.check = checksum()

    if( sendto(fd, buff, strlen(buff)+1, 0, (struct sockaddr*)&server, sizeof(server)) == -1 ){
        close(fd);
        HANDLE_ERR("sendto err");
    }
    close(fd);



    exit(EXIT_SUCCESS);
}