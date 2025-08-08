#ifndef _THREAD_ARG_H_
#define _THREAD_ARG_H_
#include <mqueue.h>

struct thread_arg{
    mqd_t** connects;
    mqd_t* mq;
    char name[256];
    int user_lenght;
    char*** users;
    char*** users_messages;
};


#endif