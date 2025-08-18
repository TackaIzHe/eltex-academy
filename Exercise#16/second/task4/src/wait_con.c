#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/signal.h>
#include <sys/epoll.h>
#include "server.h"
#include "pthread_arg.h"

#define TCP_PORT 2025
#define UDP_PORT 2520
#define handle_err(msg)     \
    do                      \
    {                       \
        unlink("queue");    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

int tcp_fd;
int udp_fd;

void kill_proc(int)
{
    close(tcp_fd);
    close(udp_fd);
    printf("Выполнилось завершение процесса\n");
    exit(EXIT_SUCCESS);
}

void *wait_con(void *)
{
    int cur_port = 5000;
    int epoll;
    const int max_fds = 2;
    int cur_fd;
    struct epoll_event epoll_fd;
    struct epoll_event repoll_fds[max_fds];
    int ev_count = 0;
    signal(10, kill_proc);
    int client_fd;
    pthread_t con_thread;
    char buff[256];
    int buff_len = 256;
    struct sockaddr_in udp_server, tcp_server, tcp_client, udp_client;
    socklen_t tcp_client_len = sizeof(tcp_client);
    socklen_t udp_client_len = sizeof(udp_client);
    struct in_addr addr;
    epoll = epoll_create1(0);

    addr.s_addr = htonl(INADDR_LOOPBACK);

    udp_server.sin_addr = addr;
    udp_server.sin_family = AF_INET;
    udp_server.sin_port = UDP_PORT;

    tcp_server.sin_addr = addr;
    tcp_server.sin_family = AF_INET;
    tcp_server.sin_port = TCP_PORT;

    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_fd == -1)
    {
        handle_err("udp socket");
    }

    tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_fd == -1)
    {
        handle_err("tcp socket");
    }

    if (bind(udp_fd, (struct sockaddr *)&udp_server, sizeof(udp_server)) == -1)
    {
        close(udp_fd);
        handle_err("udp bind");
    }

    if (bind(tcp_fd, (struct sockaddr *)&tcp_server, sizeof(tcp_server)) == -1)
    {
        close(udp_fd);
        close(tcp_fd);
        handle_err("tcp bind");
    }

    if (listen(tcp_fd, 200) == -1)
    {
        close(udp_fd);
        close(tcp_fd);
        handle_err("tcp listen");
    }

    epoll_fd.data.fd = tcp_fd;
    epoll_fd.events = EPOLLIN;
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, tcp_fd, &epoll_fd) == -1)
    {
        handle_err("epoll tcp ctl err");
    }
    epoll_fd.data.fd = udp_fd;
    epoll_fd.events = EPOLLIN;
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, udp_fd, &epoll_fd) == -1)
    {
        handle_err("epoll udp ctl err");
    }
    while (1)
    {
        ev_count = epoll_wait(epoll, repoll_fds, max_fds, -1);

        for (int i = 0; i < ev_count; i++)
        {
            if (repoll_fds[i].events & EPOLLIN)
            {
                cur_fd = repoll_fds[i].data.fd;
                if (cur_fd == tcp_fd)
                {
                    client_fd = accept(tcp_fd, (struct sockaddr *)&tcp_client, &tcp_client_len);
                    if (client_fd == -1)
                    {
                        handle_err("accept");
                    }
                    pthread_create(&con_thread,NULL,tcp_new_con,&cur_port);
                    if (send(client_fd, &cur_port, 4, 0) == -1)
                    {
                        close(client_fd);
                        handle_err("send");
                    }
                    cur_port++;
                }
                else if(cur_fd == udp_fd){
                    udp_client_len = sizeof(udp_client);
                    if(recvfrom(udp_fd,buff,buff_len,0,(struct sockaddr*)&udp_client, &udp_client_len) == -1){
                        close(udp_fd);
                        handle_err("recv");
                    }
                    
                    pthread_create(&con_thread,NULL,udp_new_con,&cur_port);
                    if (sendto(udp_fd, &cur_port, 4, 0,(struct sockaddr*)&udp_client, sizeof(udp_client)) == -1)
                    {
                        close(udp_fd);
                        handle_err("send");
                    }
                    cur_port++;
                }
            }
        }
    }
    pthread_exit(NULL);
    close(client_fd);
    close(tcp_fd);

    exit(EXIT_SUCCESS);
}