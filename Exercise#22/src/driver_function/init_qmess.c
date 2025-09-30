#include <mqueue.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "mess_struct.h"

int init_qmess(char* name_queue, int* queue_res, int* queue_req){
    mqd_t mq_res;
    mqd_t mq_req;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 2;
    attr.mq_msgsize = sizeof(struct mess);
    strcat(name_queue,"s");
    char new_name[strlen(name_queue)+1];
    new_name[0] = '/';
    new_name[1] = '\0';
    strcat(new_name,name_queue);
    
    mq_res = mq_open(new_name, O_CREAT | O_WRONLY, 0666, &attr);
    if( mq_res == (mqd_t)-1 ){
        perror("Ошибка создания очереди\n");
    }
    new_name[strlen(new_name)-1] = 'q';
    mq_req = mq_open(new_name, O_CREAT | O_RDONLY, 0666, &attr);
    if( mq_req == (mqd_t)-1 ){
        perror("Ошибка создания очереди\n");
    }
    *queue_res = mq_res;
    *queue_req = mq_req;
}