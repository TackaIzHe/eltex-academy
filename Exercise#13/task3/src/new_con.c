#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "thread_arg.h"
#include "server_stat.h"

void* res_req_mq(void* arg){
    struct thread_arg* a = (struct thread_arg*)arg;
    char new_name_mq[256] = "/mq_message_";
    strcat(new_name_mq,a->name);
    char ind[2] = "0";
    ind[0] += a->user_lenght;
    strcat(new_name_mq,ind);
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    mq = mq_open(new_name_mq, O_CREAT | O_RDWR, 0666, &attr);
    mq_send(a->mq[0],new_name_mq,strlen(new_name_mq)+1,0);
    char mess[256];
    while(server_stat){
        mq_receive(mq,mess,256,0);
        printf("%s\n",mess);
    }
}

void* new_con(void* arg){
    struct thread_arg* a = (struct thread_arg*)arg;
    int user_lenght = 0;
    pthread_t new_connectin;
    mqd_t mq;
    char mess[256];
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = 256;
    mq = mq_open("/mq_message", O_CREAT | O_RDWR, 0666, &attr);
    if(mq == (mqd_t)-1){
        perror("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }
    while(server_stat){
        mq_receive(mq,mess,256,0);
        struct thread_arg new_arg = a[0];
        new_arg.mq = &mq;
        new_arg.user_lenght = user_lenght;
        user_lenght++;
        strcpy(new_arg.name,mess);
        pthread_create(&new_connectin,NULL,res_req_mq,&new_arg);
    }
    mq_close(mq);
    mq_unlink("/mq_message");
}