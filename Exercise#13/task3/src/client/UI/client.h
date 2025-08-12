#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <mqueue.h>

int connect_func(char* name_queue, mqd_t* req, mqd_t* res);
int send_func(char* mess, mqd_t req);
void* get_mess_func(void* arg);
int get_users(mqd_t req, int* cur_pos_user);

#endif