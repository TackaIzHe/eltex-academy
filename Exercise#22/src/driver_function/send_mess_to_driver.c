#include <mqueue.h>
#include <string.h>
#include <stdio.h>
#include "mess_struct.h"
#include "../convert/convert.h"

int send_mess_to_driver(int pid, struct mess mess){
    char int_char[10];
    char name_mqueue[10];
    name_mqueue[0] ='/';
    name_mqueue[1] = '\0';
    char timer[8];

    convert_int_to_char(pid, int_char, 10);
    convert_int_to_char(mess.timer,timer,8);
    strcat(name_mqueue,int_char);
    strcat(name_mqueue,"s");
    
    mqd_t mq_res;
    mqd_t mq_req;

    mq_res = mq_open(name_mqueue,O_RDONLY);
    if(mq_res == (mqd_t)-1){
        perror("Ошибка открытия очереди\n");
    }

    name_mqueue[strlen(name_mqueue)-1] = 'q';

    mq_req = mq_open(name_mqueue,O_WRONLY);
    if(mq_req == (mqd_t)-1){
        perror("Ошибка открытия очереди\n");
    }

    if(mq_send(mq_req, timer,8,0) == -1){
        perror("Ошибка отправки сообщения\n");
    }
    char buff[8];
    if( mq_receive(mq_res,buff,8,0) == -1){
        perror("Ошибка получения сообщения\n");
    }
    printf("%s\n", buff);
    
    mq_close(mq_res);
    mq_close(mq_req);
}