#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include "new_con.h"
#include "thread_arg.h"
#include <mqueue.h>

int server_stat = 1; 

int main(){
    pthread_t await_con_thread;
    mqd_t* connects;
    connects = malloc(sizeof(mqd_t));
    char mess[256];
    char** users;
    users = malloc(8);
    *users = malloc(4);
    users[0] = NULL;
    char** users_messages;
    users_messages = malloc(8);
    *users_messages = malloc(4);
    users_messages[0] = NULL;
    
    struct thread_arg arg;
    arg.connects = &connects;
    arg.users = &users;
    arg.users_messages = &users_messages;
    pthread_create(&await_con_thread,NULL,new_con,&arg);
    while(1){
        scanf("%255s",mess);
        if(strcmp(mess,"exit") == 0){
            server_stat = 0;
            break;
        }
    }
    
    pthread_exit(NULL);
    for(int i = 0;users[i]!=NULL;i++){
        free(users[i]);
    }
    free(users);
    for(int i = 0; users_messages[i]!=NULL;i++){
        free(users_messages[i]);    
    }
    free(users_messages);
    free(connects);

    exit(EXIT_SUCCESS);
}