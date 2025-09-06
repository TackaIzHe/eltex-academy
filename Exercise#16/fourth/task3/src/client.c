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
#include <arpa/inet.h>

#define HANDLE_ERR(msg) \
    do {perror(msg); exit(EXIT_FAILURE); } while(0)


#define SERVER_PORT 50501
#define CLIENT_PORT 53531

unsigned short ip_checksum(void* vdata, size_t length) {
    unsigned short* ptr = (unsigned short*)vdata;
    int acc = 0;
    for (int i = 0; i < length; i++) {
        acc = acc + *(ptr + i);
    }
    int a = acc >> 16;
    int b = (acc & 0xffff) + a;
    printf("%x\n",htons((short)~b));
    return ~b;
}



int main(){
    int fd;
    struct sockaddr_ll server;
    char CLIENT_MAC_ADDR[] = {0xcc, 0x5e, 0xf8, 0x83, 0x2b, 0x39};
    char SERVER_MAC_ADDR[] = {0x74, 0x4c, 0xa1, 0x51, 0xc7, 0xcb};
    char buff[256];
    socklen_t server_len, client_len;
    struct in_addr server_addr;
    struct udphdr hdr_udp;
    struct iphdr hdr_ip;
    struct iphdr *recfpac_ip;
    struct udphdr *recfpac_udp;
    struct ethhdr hdr_eth;
    
    int index = if_nametoindex("wlan0");
    memcpy(server.sll_addr, SERVER_MAC_ADDR, 6);
    server.sll_family = AF_PACKET;
    server.sll_halen = 6;
    server.sll_ifindex = index;
    server.sll_hatype = 0;
    server.sll_pkttype = 0;
    server.sll_protocol = 0;
    
    memset(buff, 0, sizeof(buff));
    
    char *data = buff + sizeof(hdr_eth) + sizeof(hdr_ip) + sizeof(hdr_udp);
    
    memcpy(hdr_eth.h_dest, SERVER_MAC_ADDR, 6);
    hdr_eth.h_proto = htons(ETH_P_IP);
    memcpy(hdr_eth.h_source, CLIENT_MAC_ADDR, 6);
    
    hdr_udp.source = htons(CLIENT_PORT);
    hdr_udp.dest = htons(SERVER_PORT);
    hdr_udp.len = htons(sizeof(hdr_udp) + 4);
    
    hdr_ip.saddr = inet_addr("192.168.0.11");
    hdr_ip.daddr = inet_addr("192.168.0.17");
    hdr_ip.check = 0;
    hdr_ip.protocol = 17;
    hdr_ip.tot_len = htons(sizeof(hdr_udp) + 4);
    
    fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(fd == -1){
        HANDLE_ERR("socket err");
    }
    
    memcpy(buff, &hdr_eth, sizeof(hdr_eth));
    memcpy(buff + sizeof(hdr_eth), &hdr_ip, sizeof(hdr_ip));
    memcpy(buff + sizeof(hdr_eth) + sizeof(hdr_ip), &hdr_udp, sizeof(hdr_udp));
    memcpy(data , "HI!", (size_t)4);
    
    hdr_udp.check = ip_checksum(buff+ sizeof(hdr_eth), 10 + 10 + 4);
    
    hdr_ip.version = 4;
    hdr_ip.ihl = 5;
    hdr_ip.tos = 0;
    hdr_ip.id = 0;
    hdr_ip.frag_off = 0;
    hdr_ip.ttl = 255;
    hdr_ip.tot_len = htons(sizeof(hdr_ip) + sizeof(hdr_udp) + 4);

    memcpy(buff + sizeof(hdr_eth), &hdr_ip, sizeof(hdr_ip));

    hdr_ip.check = ip_checksum(buff+ sizeof(hdr_eth), 10);
    
    
    memcpy(buff, &hdr_eth, sizeof(hdr_eth));
    memcpy(buff + sizeof(hdr_eth), &hdr_ip, sizeof(hdr_ip));
    memcpy(buff + sizeof(hdr_eth) + sizeof(hdr_ip), &hdr_udp, sizeof(hdr_udp));
    

    if( sendto(fd, buff, sizeof(hdr_eth) + sizeof(hdr_ip) + sizeof(hdr_udp) + strlen(data)+1, 0, (struct sockaddr*)&server, sizeof(server)) == -1 ){
        close(fd);
        HANDLE_ERR("sendto err");
    }

    memcpy(server.sll_addr, CLIENT_MAC_ADDR, 6);
    
    while(1){
        memset(buff, 0, sizeof(buff));
        client_len = sizeof(server);
        if(recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)&server, &client_len) == -1){
            close(fd);
            HANDLE_ERR("recvfrom err");
        }
        short* sours_port = (short*)(buff + sizeof(hdr_eth) + sizeof(hdr_ip));
        short* dest_port = (short*)(buff + sizeof(hdr_eth) + sizeof(hdr_ip) + 2);
        char* payload = buff + sizeof(hdr_eth) + sizeof(hdr_ip) + sizeof(hdr_udp);
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