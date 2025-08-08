#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

int main(){
    mqd_t mq;
    char mess[256];
    mq = mq_open("/mq_message",O_RDWR);
    if(mq == (mqd_t)-1){
        perror("Ошибка подключения к очереди\n");
        exit(EXIT_FAILURE);
    }

    scanf("%s",mess);
    mq_send(mq,mess,strlen(mess)+1,0);
    mq_receive(mq,mess,256,0);
    mq_close(mq);

    mq = mq_open(mess,O_RDWR);
    if(mq == (mqd_t)-1){
        perror("Ошибка подключения к основной очереди");
        exit(EXIT_FAILURE);
    }
    while(1){
        scanf("%s",mess);
        mq_send(mq,mess,strlen(mess)+1,0);
    }

    exit(EXIT_SUCCESS);
}