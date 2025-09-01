#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
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
    socklen_t server_len, client_len;
    struct in_addr server_addr;
    struct udphdr hdr;
    char *data = buff + 8;
    struct iphdr *recfpac_ip;
    struct udphdr *recfpac_udp;
    
    hdr.source = htons(CLIENT_PORT);
    hdr.dest = htons(SERVER_PORT);
    hdr.len = htons(sizeof(hdr) + 4);
    hdr.check = 0;

    server_addr.s_addr = htonl(INADDR_LOOPBACK);

    server.sin_addr = server_addr;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    client.sin_addr = server_addr;
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    
    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd == -1){
        HANDLE_ERR("socket err");
    }

    memset(buff, 0, sizeof(buff));
    memcpy(buff, &hdr, sizeof(hdr));
    memcpy(data , "HI!", (size_t)4);

    if( sendto(fd, buff, sizeof(hdr) + strlen(data)+1, 0, (struct sockaddr*)&server, sizeof(server)) == -1 ){
        close(fd);
        HANDLE_ERR("sendto err");
    }
    
    memset(buff, 0, sizeof(buff));
    client_len = sizeof(client);
    while(1){
        if(recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)&client, &client_len) == -1){
            close(fd);
            HANDLE_ERR("recvfrom err");
        }
        recfpac_ip = (struct iphdr*)buff;
        int iphdr_len = recfpac_ip->ihl*4;
        recfpac_udp = (struct udphdr*) buff + iphdr_len;
        short sours_port = *(buff + iphdr_len );
        short dest_port = *(buff + iphdr_len + 2);
        char* payload = buff + iphdr_len + 8;
        printf("source port: %d\n", htons(sours_port));
        printf("dest port: %d\n", htons(dest_port));
        printf("payload: %s\n", payload);
        if(strcmp(payload, "HQ!") == 0){
            break;
        }

    }

    close(fd);



    exit(EXIT_SUCCESS);
}