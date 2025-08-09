#ifndef _THREAD_ARG_H_
#define _THREAD_ARG_H_
#include <mqueue.h>
#include "req_res.h"
#include "user_message.h"

struct thread_arg{
    struct req_res*** connects;
    mqd_t* mq;
    char name[256];
    int user_lenght;
    char*** users;
    struct user_message*** users_messages;
    int* count_message;
};


#endif