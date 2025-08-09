#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include "new_con.h"
#include "thread_arg.h"
#include "user_message.h"
#include <mqueue.h>

int server_stat = 1; 

int main(){
    pthread_t await_con_thread;
    struct req_res** connects;
    connects = malloc(8);
    connects[0] = malloc(sizeof(struct req_res));
    connects[0]->req = 0;
    connects[0]->res = 0;
    char mess[256];
    char** users;
    users = malloc(8);
    *users = malloc(4);
    users[0] = NULL;
    struct user_message** messages;
    int count_message = 0;
    messages = malloc(8);
    
    struct thread_arg arg;
    arg.connects = &connects;
    arg.users = &users;
    arg.users_messages = &messages;
    arg.count_message = &count_message;
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
    for(int i = 0; messages[i]!=NULL;i++){
        free(messages[i]);    
    }
    free(messages);
    for(int i=0;connects[i]->req != 0 && connects[i]->res != 0;i++){
        free(connects[i]);
    }
    free(connects);

    exit(EXIT_SUCCESS);
}