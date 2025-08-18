#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define handle_err(msg)     \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

void *udp_new_con(void *arg)
{
    int port = *(int *)arg;
    struct sockaddr_in server, client;
    char buff[256];
    int fd;
    int buff_len = 256;
    socklen_t client_len;
    struct in_addr addr;
    addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_addr = addr;
    server.sin_family = AF_INET;
    server.sin_port = port;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        handle_err("user sock");
    }

    if (bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        close(fd);
        handle_err("user bin");
    }

    client_len = sizeof(client);

    if(recvfrom(fd, buff, buff_len, 0, (struct sockaddr*)&client, &client_len) == -1){
        handle_err("recvfrom err");
    }

    while(1){
        if (recvfrom(fd, buff, buff_len, 0, (struct sockaddr*)&client, &client_len) == -1)
        {
            close(fd);
            handle_err("user recv error");
        }
        if (strcmp("time", buff) == 0)
        {
            strcpy(buff,"");
            time_t rawtime;
            struct tm* timeinfo;
            
            time(&rawtime);
            timeinfo = gmtime(&rawtime);

            char buffer[80];
            
            
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            if (sendto(fd, buffer, strlen(buffer) + 1, 0, (struct sockaddr*)&client, sizeof(client)) == -1)
            {
                close(fd);
                handle_err("user send err");
            }
        }
        else if(strcmp(buff,"exit")){
            close(fd);
            exit(EXIT_SUCCESS);    
        }
        else{
            if (sendto(fd, "Not Found", 10, 0, (struct sockaddr*)&client, sizeof(client)) == -1)
            {
                close(fd);
                handle_err("user send err");
            }
        }
        strcpy(buff,"");
    }
    close(fd);
    exit(EXIT_SUCCESS);
}