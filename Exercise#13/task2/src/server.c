#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>

int main(){
    mqd_t mq_res;
    mqd_t mq_req;
    struct mq_attr attr;
    char mess[10];
    attr.mq_flags = 0;
    attr.mq_maxmsg = 2;
    attr.mq_msgsize = 10;
    mq_res = mq_open("/mqueue_res", O_CREAT | O_WRONLY, 0666, &attr);
    if( mq_res == (mqd_t)-1 ){
        perror("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }

    mq_req = mq_open("/mqueue_req", O_CREAT | O_RDONLY, 0666, &attr);
    if( mq_req == (mqd_t)-1 ){
        perror("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }

    if(mq_send(mq_res, "Hi!",4,0) == -1){
        perror("Ошибка отправки сообщения\n");
        exit(EXIT_FAILURE);
    }

    if( mq_receive(mq_req,mess,10,0) == -1){
        perror("Ошибка получения сообщения\n");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", mess);
    mq_close(mq_req);
    mq_unlink("/mqueue_req");

    mq_close(mq_res);
    mq_unlink("/mqueue_res");

    exit(EXIT_SUCCESS);
}