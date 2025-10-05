#ifndef _SERVER_FUNC_H_
#define _SERVER_FUNC_H_

int new_con(struct sockaddr_in client);
int convert_int_to_char(int num, char* str, int lenght);
void sigint(int);

#endif