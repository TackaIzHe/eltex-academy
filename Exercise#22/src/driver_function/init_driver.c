#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <time.h>
#include <mqueue.h>
#include <string.h>
#include "../list_function/list_func.h"
#include "../convert/convert.h"
#include "ini_queue.h"
#include "mess_struct.h"

#define max_fds 1

#define handle_err(msg)\
    do{perror(msg);}while(0)

int init_driver(struct list_drivers* list, int* lenght){
    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0){
        char name_queue[10];
        int pid = getpid();
        int epoll;
        mqd_t queue_res;
        mqd_t queue_req;
        int ev_count = 0;
        struct epoll_event epoll_fd;
        struct epoll_event repoll_fds[max_fds];
        epoll = epoll_create(0);
        add(list,pid,lenght);
        printf("Драйвер создан PID: %d\n", pid);

        epoll = epoll_create1(0);

        convert_int_to_char(pid, name_queue, 10);

        if(init_qmess(name_queue, &queue_res, &queue_req) == -1){
            perror("Err init queue");
            return -1;
        }

        epoll_fd.data.fd = queue_req;
        epoll_fd.events = EPOLLIN;
        if (epoll_ctl(epoll, EPOLL_CTL_ADD, queue_req, &epoll_fd) == -1)
        {
            printf("fd queue: %d", queue_req);
            handle_err("epoll queue ctl err");
        }
        int cur_time = 0;
        while(1){
            ev_count = epoll_wait(epoll, repoll_fds, max_fds, 1000);
            if(ev_count>0){
                char buff[100];
                if( mq_receive(repoll_fds[0].data.fd,buff,100,0) == -1){
                    perror("Ошибка получения сообщения\n");
                }
                if(cur_time<= time(NULL)){
                    int timer = 0;
                    cur_time = time(NULL);
                    convert_char_to_int(buff,&timer);
                    cur_time += timer;
                    struct list_drivers* cur_item = (struct list_drivers*)get(list,pid,*lenght);
                    strcpy(cur_item->status, "Busy");
                    if( mq_send(queue_res,"OK",3,0) == -1){
                        perror("Ошибка отправки сообщения\n");
                    }
                }
                else{
                    strcpy(buff, "Busy");
                    if( mq_send(queue_res,buff,5,0) == -1){
                        perror("Ошибка отправки сообщения\n");
                    }
                }
                ev_count--;
            }
            if((cur_time != 0) && (cur_time<=time(NULL))){
                struct list_drivers* cur_item = (struct list_drivers*)get(list,pid,*lenght);
                strcpy(cur_item->status, "Avalible");
            }
        }
        
    }else{
        return 0;   
    }
}
//для создания очередей использовать systemV
//создать 2 очереди одна для получения другая для отправки дочернему процесу
//создать epoll для двух очередей
//слушать очередь при получении команды засыпать просыпаться и отпровлять в очередь сообщение и поновой