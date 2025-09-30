#ifndef _LIST_FUNC_H_
#define _LIST_FUNC_H_

#include "list_struct.h"

int add(struct list_drivers* list , pid_t pid, int* lenght);
int get_all(struct list_drivers* list, int lenght);

//void* a = get(drivers,100,list_lenght); 
//struct list_drivers* c = (struct list_drivers*)a;
void* get(struct list_drivers* list , pid_t pid, int lenght); 

#endif