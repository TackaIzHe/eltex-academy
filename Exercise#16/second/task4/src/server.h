#ifndef _SERVER_H_
#define _SERVER_H_

#include "pthread_arg.h"

void* wait_con(void*);
void *tcp_new_con(void *arg);
void *udp_new_con(void *arg);
int create_threads(struct pthread_arg** workers, int len);

#endif