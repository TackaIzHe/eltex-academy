#ifndef _SERVER_H_
#define _SERVER_H_

#include "pthread_arg.h"

void* wait_con(void*);
void* new_con(void*);
int create_threads(struct pthread_arg** workers, int len);

#endif