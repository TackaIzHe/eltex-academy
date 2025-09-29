#ifndef _COMAND_FUNC_H_
#define _COMAND_FUNC_H_

#include <unistd.h>
#include "../list_function/list_func.h"

int create_driver(struct list_drivers* list, int* lenght);
int send_task(pid_t pid, int timer, int* lenght);
int get_status(pid_t pid, int* lenght);
int get_drivers(struct list_drivers* list, int* lenght);
int del_driver(pid_t pid, int* lenght);

#endif