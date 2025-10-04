#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
#include "network_pseudo_title.h"
#include "check_sum.h"

int set_header(char** buff, int buff_lenght, char* data, struct sockaddr_in dest, struct sockaddr_in sourc){
    char buffer[buff_lenght];
    struct udphdr hdr_udp;
    struct iphdr hdr_ip;
    struct network_pseudo_title pseudo_ip_title;

    if( (strlen(data)+1) & 1){
        strcat(data," ");
    }
    memset(buffer, 0, buff_lenght);
    memset(*buff, 0, buff_lenght);

    hdr_udp.dest = dest.sin_port;
    hdr_udp.source = sourc.sin_port;
    hdr_udp.len = htons( sizeof(hdr_udp) + (strlen(data)+1) );
    hdr_udp.check = 0;

    pseudo_ip_title.daddr = dest.sin_addr.s_addr;
    pseudo_ip_title.saddr = sourc.sin_addr.s_addr;
    pseudo_ip_title.proto = 17;
    pseudo_ip_title.zero = 0;
    pseudo_ip_title.tot_len = htons( (strlen(data)+1) + (sizeof(hdr_udp)) );
    
    memcpy(buffer, &pseudo_ip_title, sizeof(pseudo_ip_title));
    memcpy(buffer + sizeof(pseudo_ip_title), &hdr_udp, sizeof(hdr_udp));
    memcpy(buffer + sizeof(pseudo_ip_title) + sizeof(hdr_udp), data, (strlen(data)+1) );

    hdr_udp.check = checksum(buffer, ( sizeof(pseudo_ip_title) + sizeof(hdr_udp) + (strlen(data)+1) ) / 2 );

    hdr_ip.version = 4;
    hdr_ip.ihl = 5;
    hdr_ip.tos = 0;
    hdr_ip.tot_len = htons(sizeof(hdr_ip) + sizeof(hdr_udp) + strlen(data) +1);
    hdr_ip.id = 0;
    hdr_ip.frag_off = 0;
    hdr_ip.ttl = 255;
    hdr_ip.protocol = 17;
    hdr_ip.saddr = sourc.sin_addr.s_addr;
    hdr_ip.daddr = dest.sin_addr.s_addr;
    hdr_ip.check = 0;
    

    memcpy(*buff, &hdr_ip, sizeof(hdr_ip));
    memcpy(*buff+ sizeof(hdr_ip), &hdr_udp, sizeof(hdr_udp));
    memcpy(*buff+ sizeof(hdr_ip) + sizeof(hdr_udp), data, strlen(data)+1);
    hdr_ip.check = checksum(buffer, ( sizeof(pseudo_ip_title) + sizeof(hdr_udp) + (strlen(data)+1) ) / 2 );
    memcpy(*buff, &hdr_ip, sizeof(hdr_ip));
    
}