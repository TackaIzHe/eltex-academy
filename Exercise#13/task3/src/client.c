#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <pthread.h>

struct pthread_arg{
    mqd_t res;
};

void* reader_func(void* arg){
    struct pthread_arg* a = (struct pthread_arg*)arg;
    char mess[256];
    while(1){
        mq_receive(a->res,mess,256,0);
        printf("%s\n",mess);
    }
}

int main(){
    mqd_t mq;
    mqd_t res;
    mqd_t req;
    pthread_t reader;
    struct pthread_arg arg;
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

    res = mq_open(mess,O_RDONLY);
    if(res == (mqd_t)-1){
        perror("Ошибка подключения к основной очереди");
        exit(EXIT_FAILURE);
    }
    mess[14] = 'q';
    req = mq_open(mess,O_WRONLY);
    if(req == (mqd_t)-1){
        perror("Ошибка подключения к основной очереди");
        exit(EXIT_FAILURE);
    }
    arg.res = res;
    pthread_create(&reader, NULL, reader_func, &arg);
    while(1){
        scanf("%s",mess);
        mq_send(req,mess,strlen(mess)+1,0);
    }
    pthread_exit(NULL);
    exit(EXIT_SUCCESS);
}