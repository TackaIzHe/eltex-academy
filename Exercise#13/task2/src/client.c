#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>

int main(){
    mqd_t mq_res;
    mqd_t mq_req;
    char mess[10];
    mq_res = mq_open("/mqueue_res",O_RDONLY);
    if(mq_res == (mqd_t)-1){
        perror("Ошибка открытия очереди\n");
        exit(EXIT_FAILURE);
    }

    mq_req = mq_open("/mqueue_req",O_WRONLY);
    if(mq_req == (mqd_t)-1){
        perror("Ошибка открытия очереди\n");
        exit(EXIT_FAILURE);
    }

    if( mq_receive(mq_res,mess,10,0) == -1){
        perror("Ошибка получения сообщения\n");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", mess);
    if(mq_send(mq_req, "Hello!",7,(unsigned int)1) == -1){
        perror("Ошибка отправки сообщения\n");
        exit(EXIT_FAILURE);
    }
    mq_close(mq_res);
    mq_close(mq_req);
    exit(EXIT_SUCCESS);
}