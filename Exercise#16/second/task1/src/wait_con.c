#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/signal.h>
#include "server.h"
#include "pthread_arg.h"

#define PORT 2025
#define handle_err(msg)     \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int fd;

void kill_proc(int){
    close(fd);
    printf("Выполнилось завершение процесса\n");
    exit(EXIT_SUCCESS);
}

void *wait_con(void *)
{
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
        int cur_id = id;
        int user_fd;
        struct pthread_arg p_arg;
        
        p_arg.user_sock.sin_port = cur_id;
        p_arg.user_sock.sin_addr = addr;
        p_arg.user_sock.sin_family = AF_INET;
        
        client_fd = accept(fd, (struct sockaddr *)&client, &client_len);
        if (client_fd == -1)
        {
            handle_err("accept");
        }
        
        pthread_create(&con_thread, NULL, new_con, &cur_id);
        if (send(client_fd, &cur_id, 4, 0) == -1)
        {
            close(fd);
            close(client_fd);
            handle_err("send");
        }
        id++;
    }
    pthread_exit(NULL);
    close(client_fd);
    close(fd);

    exit(EXIT_SUCCESS);
}