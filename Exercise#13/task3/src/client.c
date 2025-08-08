#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

int main(){
    mqd_t mq;
    char mess[256];
    mq = mq_open("/mq_message",O_WRONLY);
    if(mq == (mqd_t)-1){
        perror("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }

    scanf("%s",mess);
    mq_send(mq,mess,strlen(mess)+1,0);
    mq_close(mq);

    exit(EXIT_SUCCESS);
}