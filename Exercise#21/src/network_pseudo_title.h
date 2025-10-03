#ifndef _NETWORK_PSEUDO_TITLE_H_
#define _NETWORK_PSEUDO_TITLE_H_

#include <cstdint>
struct network_pseudo_title{
    uint32_t saddr;
    uint32_t daddr;
    uint8_t zero;
    uint8_t proto;
    uint16_t tot_len;
};

#endif