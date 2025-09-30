#ifndef _COMAND_FUNC_H_
#define _COMAND_FUNC_H_

#include <unistd.h>
#include "../list_function/list_func.h"

int create_driver(void** addr_shm);
int send_task(pid_t pid, int timer);
int get_status(pid_t pid);
int get_drivers(void** addr_shm);
int send_comand(pid_t pid, char* comand);

#endif