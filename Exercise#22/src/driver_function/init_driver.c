#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "../list_function/list_func.h"

int init_child_driver(char* name_qmess){

}

int init_driver(struct list_drivers* list, int* lenght){
    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0){
        int epoll_fd = 0;
        int pid = getpid();
        epoll_fd = epoll_create(0);
        add(list,pid,lenght);
        printf("Драйвер создан PID: %d\n", pid);
        
    }else{
        return 0;   
    }
}
//для создания очередей использовать systemV
//создать 2 очереди одна для получения другая для отправки дочернему процесу
//создать epoll для двух очередей
//слушать очередь при получении команды засыпать просыпаться и отпровлять в очередь сообщение и поновой