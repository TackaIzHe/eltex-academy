#ifndef _PTHREAD_ARG_H_
#define _PTHREAD_ARG_H_

#include <netinet/in.h>

struct pthread_arg{
    struct sockaddr_in user_sock;
    int user_fd; 
};

#endif