#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/signal.h>
#include <malloc.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include "server.h"
#include "pthread_arg.h"
#include "msgbuf.h"

#define PORT 2025
#define handle_err(msg)     \
    do { unlink("queue"); perror(msg); exit(EXIT_FAILURE); } while (0)

int fd;
struct pthread_arg* workers;
int queue;

void kill_proc(int){
    msgctl(queue,IPC_RMID,NULL);
    unlink("queue");
    close(fd);
    free(workers);    
    printf("Выполнилось завершение процесса\n");
    exit(EXIT_SUCCESS);
}

void *wait_con(void *)
{
    struct msgbuf buf;
    buf.mtype = 1;
    key_t key;
    workers = malloc(sizeof(struct pthread_arg) * 10);
    
    create_threads(&workers, 10);

    key = ftok("queue",1);
    if(key == -1){
        handle_err("ftok err");
    }
    queue = msgget(key,0666 | IPC_CREAT);
    if(queue == -1){
        handle_err("msgget err");
    }

    signal(10,kill_proc);
    int client_fd;
    pthread_t con_thread;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);
    struct in_addr addr;
    addr.s_addr = htonl(INADDR_LOOPBACK);

    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = PORT;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        handle_err("socket");
    }

    if (bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        close(fd);
        handle_err("bind");
    }

    if (listen(fd, 200) == -1)
    {
        close(fd);
        handle_err("listen");
    }
    while (1)
    {        
        client_fd = accept(fd, (struct sockaddr *)&client, &client_len);
        if (client_fd == -1)
        {
            handle_err("accept");
        }
        buf.client_fd = client_fd;
        
        int stat = msgsnd(queue, &buf, sizeof(buf),0);
        if(stat == -1){
            handle_err("msgsnd err");
        }
        
    }
    free(workers);
    pthread_exit(NULL);
    close(client_fd);
    close(fd);

    exit(EXIT_SUCCESS);
}