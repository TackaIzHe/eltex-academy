#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include "server.h"

#define handle_err(msg)\
    do{unlink("queue"); perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    int queue;
    char buff[256];
    pthread_t lisent_soc;
    queue = open("queue",O_CREAT,0666);
    if(queue == -1){
        handle_err("queue create err");
    }
    close(queue);
    pthread_create(&lisent_soc,NULL,wait_con,NULL);
    while(1){
        scanf("%s",buff);
        if(strcmp(buff,"exit") == 0){
            raise(10);
        }   
    }
    pthread_exit(NULL);
    exit(EXIT_SUCCESS);

}