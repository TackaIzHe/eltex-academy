#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/signal.h>
#include "server.h"

#define PORT 2025
#define handle_err(msg)\
    do{perror(msg); exit(EXIT_FAILURE);}while(0)

void kill_proc(int){
    printf("Выполнилось завершение процесса\n");
    exit(EXIT_SUCCESS);
}

int main(){
    signal(10,kill_proc);
    char buff[256];
    pthread_t lisent_soc;
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