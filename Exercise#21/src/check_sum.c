#include <stdlib.h>

unsigned short checksum(void* vdata, size_t length) {
    unsigned short* ptr = (unsigned short*)vdata;
    int acc = 0;
    for (int i = 0; i < length; i++) {
        acc = acc + *(ptr + i);
    }
    int a = acc >> 16;
    int b = (acc & 0xffff) + a;
    return ~b;
}