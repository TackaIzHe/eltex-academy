#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include "thread_arg.h"
#include "server_stat.h"

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void* res_req_mq(void* arg){
    struct thread_arg* a = (struct thread_arg*)arg;
    char name[256];
    strcpy(name,a->name);
    char new_name_res[256] = "/mq_message_res_";
    char new_name_req[256] = "/mq_message_req_";
    strcat(new_name_res,name);
    strcat(new_name_req,name);
    char ind[2] = "0";
    ind[0] += a->user_lenght;
    strcat(new_name_req,ind);
    strcat(new_name_res,ind);
    mqd_t req;
    mqd_t res;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    res = mq_open(new_name_res, O_CREAT | O_WRONLY, 0666, &attr);
    if(res == (mqd_t)-1){
        perror("Ошибка создания очереди\n");
    }
    req = mq_open(new_name_req, O_CREAT | O_RDONLY, 0666, &attr);
    if(req == (mqd_t)-1){
        perror("Ошибка создания очереди\n");
    }

    pthread_mutex_lock(&m1);
    int i = 0;
    while(1){
        if(a->connects[0][0][i].res == 0 && a->connects[0][0][i].req == 0){
            a->connects[0][0][i].req = req;
            a->connects[0][0][i].res = res;
            a->users[0] = realloc(a->users[0], (a->user_lenght+1) * 8);
            a->users[0][i] = realloc(a->users[0][i], (a->user_lenght+1) * 256);
            strcpy(a->users[0][i],name);
            a->connects[0][0][i+1].req = 0;
            a->connects[0][0][i+1].res = 0;
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&m1);

    mq_send(a->mq[0],new_name_res,strlen(new_name_res)+1,0);

    char mess[256];

    mq_send(res,";;users-list;;",strlen(";;users-list;;"),0);
    for(int j = 0;j<a->user_lenght;j++){
        mq_send(res,a->users[0][j],256,0);
    }
    mq_send(res,";;users-list-end;;",strlen(";;users-list-end;;"),0);
    
    for(int j = 0;j<a->count_message[0];j++){
        char buff[256];
        strcpy(buff,"");
        strcat(buff,a->users_messages[0][j]->user);
        strcat(buff,": ");
        strcat(buff,a->users_messages[0][j]->message);
        mq_send(res,buff,256,0);
    }

    
    for(int j=0;j>=0;j++){
        if(a->connects[0][0][j].req == 0){
            break;
        }
        mq_send(a->connects[0][0][j].res,";;user-connect;;",strlen(";;user-connect;;")+1,0);
        mq_send(a->connects[0][0][j].res,a->name,strlen(a->name)+1,0);
        mq_send(a->connects[0][0][j].res,";;user-connect-end;;",strlen(";;user-connect-end;;")+1,0);
    }

    while(server_stat){
        char cur[256];
        strcpy(cur,"");
        i = 0;
        mq_receive(req,mess,256,0);

        pthread_mutex_lock(&m2);
        a->count_message[0] = a->count_message[0] + 1; 
        a->users_messages[0] = realloc(a->users_messages[0],a->count_message[0] * 8);
        a->users_messages[0][a->count_message[0]-1] = malloc(sizeof(struct user_message));
        strcpy(a->users_messages[0][a->count_message[0]-1]->message,mess);
        strcpy(a->users_messages[0][a->count_message[0]-1]->user,name);
        pthread_mutex_unlock(&m2);
        
        strcat(cur,name);
        strcat(cur,": ");
        strcat(cur,mess);
        while(1){
            if(a->connects[0][0][i].req == 0){
                break;
            }

            mq_send(a->connects[0][0][i].res,cur,strlen(cur)+1,0);
            i++;
        }
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
        pthread_mutex_lock(&m1);
        new_arg.connects[0][0] = realloc(new_arg.connects[0][0], (new_arg.user_lenght + 2) * sizeof(struct req_res));
        pthread_mutex_unlock(&m1);
        strcpy(new_arg.name,mess);
        pthread_create(&new_connectin,NULL,res_req_mq,&new_arg);
    }
    mq_close(mq);
    mq_unlink("/mq_message");
}