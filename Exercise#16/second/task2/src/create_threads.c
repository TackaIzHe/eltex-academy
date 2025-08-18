#include <pthread.h>
#include "pthread_arg.h"
#include "server.h"

#define PORT 2050

int create_threads(struct pthread_arg** workers, int len){
    int cur_port = PORT;
    pthread_t pot;
    for(int i=0;i<len;i++){
        workers[0][i].port = cur_port + i;
        workers[0][i].stat = 0;
        pthread_create(&pot,NULL,new_con,&(workers[0][i]));
    }
    
    return 0;
}