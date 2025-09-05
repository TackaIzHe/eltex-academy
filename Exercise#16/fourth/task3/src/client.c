#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <string.h>

#define HANDLE_ERR(msg) \
    do {perror(msg); exit(EXIT_FAILURE); } while(0)

#define CLIENT_MAC_ADDR 0xcc5ef8832b3900
#define SERVER_MAC_ADDR 0x744ca151c7cb00

#define SERVER_PORT 5050
#define CLIENT_PORT 5353

int main(){
    int fd;
    int one = 1;
    char buff[256];
    struct sockaddr_ll server, client;
    socklen_t server_len, client_len;
    struct in_addr server_addr;
    struct udphdr hdr_udp;
    struct iphdr hdr_ip;
    char *data = buff + 8 + 20;
    struct iphdr *recfpac_ip;
    struct udphdr *recfpac_udp;
    
    hdr_ip.version = 4;
    hdr_ip.ihl = 5;
    hdr_ip.tos = 0;
    hdr_ip.tot_len = 32;
    hdr_ip.id = 0;
    hdr_ip.frag_off = 0;
    hdr_ip.ttl = 255;
    hdr_ip.protocol = 17;
    hdr_ip.check = 0;
    hdr_ip.saddr = htonl(INADDR_LOOPBACK);
    hdr_ip.daddr = htonl(INADDR_LOOPBACK);

    hdr_udp.source = htons(CLIENT_PORT);
    hdr_udp.dest = htons(SERVER_PORT);
    hdr_udp.len = htons(sizeof(hdr_udp) + 4);
    hdr_udp.check = 0;

    int index = if_nametoindex("wlan0");
    strcpy(server.sll_addr, SERVER_MAC_ADDR);
    server.sll_family = AF_PACKET;
    server.sll_halen = 6;
    server.sll_ifindex = index;
    server.sll_hatype = 0;
    server.sll_pkttype = 0;
    server.sll_protocol = 0;

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd == -1){
        HANDLE_ERR("socket err");
    }

    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) == -1) {
        close(fd);
        HANDLE_ERR("setsockopt err");
    }

    memset(buff, 0, sizeof(buff));
    memcpy(buff, &hdr_ip, sizeof(hdr_ip));
    memcpy(buff + sizeof(hdr_ip), &hdr_udp, sizeof(hdr_udp));
    memcpy(data , "HI!", (size_t)4);

    if( sendto(fd, buff, sizeof(hdr_ip) + sizeof(hdr_udp) + strlen(data)+1, 0, (struct sockaddr*)&server, sizeof(server)) == -1 ){
        close(fd);
        HANDLE_ERR("sendto err");
    }
    
    memset(buff, 0, sizeof(buff));
    client_len = sizeof(client);
    while(1){
        if(recvfrom(fd, buff, sizeof(buff), 0, 0, 0) == -1){
            close(fd);
            HANDLE_ERR("recvfrom err");
        }
        recfpac_ip = (struct iphdr*)buff;
        int iphdr_len = recfpac_ip->ihl*4;
        recfpac_udp = (struct udphdr*) buff + iphdr_len;
        short* sours_port = (short*)(buff + iphdr_len);
        short* dest_port = (short*)(buff + iphdr_len + 2);
        char* payload = buff + iphdr_len + 8;
        printf("source port: %d\n", htons(*sours_port));
        printf("dest port: %d\n", htons(*dest_port));
        printf("payload: %s\n", payload);
        if(htons(*sours_port) == SERVER_PORT){
            break;
        }

    }

    close(fd);



    exit(EXIT_SUCCESS);
}