#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "msgbuf.h"

int main(){
    key_t key;
    int queue_id;
    int queue;
    struct msgbuf msg;
    struct msgbuf req_msg;
    
    queue = open("queue",O_CREAT,0666);
    if(queue == -1){
        printf("Ошибка создания файла очереди\n");
        exit(EXIT_FAILURE);
    }
    close(queue);

    key = ftok("queue",1);
    queue_id = msgget(key, 0666 | IPC_CREAT);
    if(queue_id == -1){
        printf("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }
    
    msg.mtype = 1;
    strcpy(msg.mtext,"Hi!");
    int status = msgsnd(queue_id,&msg,strlen(msg.mtext)+1,0);
    if(status == -1){
        printf("Ошибка отправки сообщения\n");
        exit(EXIT_FAILURE);
    }

    msgrcv(queue_id,&req_msg,100,2,0);
    printf("%s\n",req_msg.mtext);

    msgctl(queue_id,IPC_RMID,NULL);
    unlink("queue");
    exit(EXIT_SUCCESS);
}