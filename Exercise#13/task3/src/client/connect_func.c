#include <mqueue.h>
#include <fcntl.h>
#include <stdlib.h>

int connect_func(char* name_queue, mqd_t* req, mqd_t* res){

    *res = mq_open(name_queue,O_RDONLY);
    if(*res == (mqd_t)-1){
        // perror("Ошибка подключения к основной очереди");
        exit(EXIT_FAILURE);
    }
    name_queue[14] = 'q';
    *req = mq_open(name_queue,O_WRONLY);
    if(*req == (mqd_t)-1){
        // perror("Ошибка подключения к основной очереди");
        exit(EXIT_FAILURE);
    }

    return 0;
}