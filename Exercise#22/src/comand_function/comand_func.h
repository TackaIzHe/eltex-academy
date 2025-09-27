#ifndef _COMAND_FUNC_H_
#define _COMAND_FUNC_H_

#include <unistd.h>
#include "../list_function/list_func.h"

int create_driver(struct list_drivers* list);
int send_task(pid_t pid, int timer);
int get_status(pid_t pid);
int get_drivers(struct list_drivers* list);
int del_driver(pid_t pid);

#endif