#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "pthread_arg.h"

#define handle_err(msg)     \
    do                      \
    {                       \
        perror(msg);        \
    } while (0)

void *new_con(void *arg)
{
    struct pthread_arg *port = (struct pthread_arg *)arg;
    struct sockaddr_in server, client;
    char buff[256];
    int fd;
    int new_fd;
    int buff_len = 256;
    socklen_t client_len;
    struct in_addr addr;
    addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = port->port;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        handle_err("user sock");
    }

    while(1){
        port->port = port->port + 10;
        server.sin_port = port->port;
        if (bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
            close(fd);
            handle_err("user bin");
        }else{
            break;
        }
    }

    if (listen(fd, 1) == -1)
    {
        close(fd);
        handle_err("user listen");
    }
    while (1)
    {
        port->stat = 0;
        client_len = sizeof(client);
        new_fd = accept(fd, (struct sockaddr *)&client, &client_len);
        if (new_fd == -1)
        {
            close(fd);
            handle_err("user accept error");
        }
        port->stat = 1;
        while (1)
        {
            if (recv(new_fd, buff, buff_len, 0) == -1)
            {
                close(new_fd);
                close(fd);
                handle_err("user recv error");
            }
            if (strcmp("time", buff) == 0)
            {
                strcpy(buff, "");
                time_t rawtime;
                struct tm *timeinfo;

                time(&rawtime);
                timeinfo = gmtime(&rawtime);

                char buffer[80];

                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
                if (send(new_fd, buffer, strlen(buffer) + 1, 0) == -1)
                {
                    close(new_fd);
                    close(fd);
                    handle_err("user send err");
                }
            }
            else if (strcmp(buff, "exit"))
            {
                port->stat = 0;
                close(new_fd);
                break;
            }
            else
            {
                if (send(new_fd, "Not Found", 10, 0) == -1)
                {
                    close(new_fd);
                    close(fd);
                    handle_err("user send err");
                }
            }
            strcpy(buff, "");
        }
    }
    close(fd);
    close(new_fd);
    exit(EXIT_SUCCESS);
}