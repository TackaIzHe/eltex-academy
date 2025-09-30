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
#include "sem_shm.h"

#define max_fds 1

#define handle_err(msg)\
    do{perror(msg);}while(0)

int init_driver(void** lenght_and_list){
    pid_t pid;
    int status;
    pid = fork();
    printf("%d\n",pid);
    if(pid == 0){
        reopen_shm(lenght_and_list);
        struct list_drivers* start = (struct list_drivers*)(*lenght_and_list+4);
        int* lenght = (int*)*lenght_and_list;
        char name_queue[10];
        int pid = getpid();
        int epoll;
        mqd_t queue_res;
        mqd_t queue_req;
        int ev_count = 0;
        struct epoll_event epoll_fd;
        struct epoll_event repoll_fds[max_fds];
        epoll = epoll_create(0);
        add(start,pid,lenght);
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
                if(strcmp(buff,"stat") == 0){
                    struct list_drivers* cur_item = (struct list_drivers*)get(start,pid,*lenght);
                    cur_item->status[7] = '\0';
                    if( mq_send(queue_res,cur_item->status,8,0) == -1){
                        perror("Ошибка отправки сообщения\n");
                    }
                }
                else if(strcmp(buff, "exit") == 0){
                    strcpy(buff, "OK");
                    if( mq_send(queue_res,buff,3,0) == -1){
                        perror("Ошибка отправки сообщения\n");
                    }
                    exit(EXIT_SUCCESS);
                }
                else if(cur_time<= time(NULL)){
                    int timer = 0;
                    cur_time = time(NULL);
                    convert_char_to_int(buff,&timer);
                    cur_time += timer;
                    struct list_drivers* cur_item = (struct list_drivers*)get(start,pid,*lenght);
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
                struct list_drivers* cur_item = (struct list_drivers*)get(start,pid,*lenght);
                strcpy(cur_item->status, "Available");
            }
        }
    }else{
    }
}