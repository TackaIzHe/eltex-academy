#ifndef _SOCKET_FUNC_H_
#define _SOCKET_FUNC_H_

#include <netinet/in.h>
#include "mess_struct.h"

int set_header(char* buff, int buff_lenght, char* data, struct sockaddr_in dest, struct sockaddr_in sourc);
int open_socket(int* fd);
int get_mess(int* fd, struct mess* message, struct sockaddr_in* client);
int send_mess(int* fd, char* buff, struct sockaddr_in* dest);

#endif