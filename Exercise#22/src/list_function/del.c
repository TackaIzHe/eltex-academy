#include <malloc.h>
#include "list_struct.h"

int del(struct list_drivers* list, pid_t pid, int* lenght){
    struct list_drivers* cur = list;
    for (int i = 0; i < *lenght; i++)
    {
            if(cur->pid_driver == pid){
                cur->lees->next = cur->next ;
                cur->next->lees = cur->lees;
                *lenght = *lenght - 1;
                free(cur);
                break;
            }

        cur = cur->next;
    }
}