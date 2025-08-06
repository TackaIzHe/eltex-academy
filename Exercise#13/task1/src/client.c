#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgbuf.h"
#include <stdio.h>
#include <string.h>

int main(){
    int key;
    int queue_id;
    struct msgbuf req_msg;
    struct msgbuf res_msg;
    key = ftok("queue",1);
    queue_id = msgget(key, 0666 | IPC_CREAT);
    if(queue_id == -1){
        printf("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }

    msgrcv(queue_id,&res_msg,100,1,0);
    printf("%s\n",res_msg.mtext);

    req_msg.mtype = 2;
    strcpy(req_msg.mtext,"Hello!");

    msgsnd(queue_id,&req_msg,100,0);

    exit(EXIT_SUCCESS);
}