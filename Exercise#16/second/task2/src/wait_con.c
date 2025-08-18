#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/signal.h>
#include <malloc.h>
#include "server.h"
#include "pthread_arg.h"

#define PORT 2025
#define handle_err(msg)     \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int fd;
struct pthread_arg* workers;

void kill_proc(int){
    close(fd);
    free(workers);    
    printf("Выполнилось завершение процесса\n");
    exit(EXIT_SUCCESS);
}

void *wait_con(void *)
{
    workers = malloc(sizeof(struct pthread_arg) * 10);
    
    create_threads(&workers, 10);

    signal(10,kill_proc);
    int client_fd;
    int id = PORT + 1;
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
        int user_fd;
        
        client_fd = accept(fd, (struct sockaddr *)&client, &client_len);
        if (client_fd == -1)
        {
            handle_err("accept");
        }
        int pport = 0;
        while(1){
            pport = 0;
            for(int i =0;i<10;i++){
                if(workers[i].stat == 0){
                    pport = workers[i].port;
                    break;
                }
            }
            if(pport != 0){
                break;
            }
        }

        if (send(client_fd, &pport, 4, 0) == -1)
        {
            close(fd);
            close(client_fd);
            handle_err("send");
        }
        id++;
    }
    free(workers);
    pthread_exit(NULL);
    close(client_fd);
    close(fd);

    exit(EXIT_SUCCESS);
}