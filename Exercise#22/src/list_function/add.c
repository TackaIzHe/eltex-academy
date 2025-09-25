#include <malloc.h>
#include <string.h>
#include "list_struct.h"

int add(struct list_drivers* list , pid_t pid, int* lenght){
    if(*lenght == 0){
        list->pid_driver = pid;
        strcpy(list->status, "Available");
        list->last = list;
        list->next = 0;
        list->lees = 0;

    }else{
        struct list_drivers* elem;
    
        elem = malloc(sizeof(struct list_drivers));
    
        elem->pid_driver = pid;
        strcpy(elem->status, "Available");
        elem->next = 0;
        elem->lees = list->last;
        elem->last = elem;

        list->last->next = elem;
        list->last = elem;
    }
    *lenght = *lenght + 1;
    return 0;
}