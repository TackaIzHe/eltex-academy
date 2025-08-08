#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include "thread_arg.h"
#include "server_stat.h"

void* new_con(void* arg){ //name
    struct thread_arg* a = (struct thread_arg*)arg;
    mqd_t mq;
    while(server_stat){
        sleep(1);
        printf("a\n");
    }
}