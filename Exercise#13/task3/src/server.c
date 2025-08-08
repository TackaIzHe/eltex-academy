#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include "new_con.h"
#include "thread_arg.h"

int server_stat = 1; 

int main(){
    pthread_t await_con_thread;
    mqd_t mq;
    char mess[256];
    char** users;
    users = malloc(8);
    users[0] = malloc(4);
    users[0] = NULL;
    char** users_messages;
    users_messages = malloc(8);
    users_messages[0] = malloc(4);
    users_messages[0] = NULL;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = 256;
    mq = mq_open("/mq_message", O_CREAT | O_RDWR, 0666, &attr);
    if(mq == (mqd_t)-1){
        perror("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }
    struct thread_arg arg;
    arg.users = &users;
    arg.users_messages = &users_messages;
    pthread_create(&await_con_thread,NULL,new_con,&arg);
    while(1){
        scanf("%255s",mess);
        if(strcmp(mess,"exit") == 0){
            server_stat = 0;
            break;
        }
    }
    
    pthread_exit(NULL);
    mq_close(mq);
    mq_unlink("/mq_message");
    free(users);
    free(users_messages);

    exit(EXIT_SUCCESS);
}