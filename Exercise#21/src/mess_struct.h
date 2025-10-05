#ifndef _MESS_STRUCT_H_
#define _MESS_STRUCT_H_

#include <netinet/ip.h>
#include <netinet/udp.h>

struct mess{
    struct iphdr ip_hdr;
    struct udphdr udp_hdr;
    char payload[1024];
};


#endif