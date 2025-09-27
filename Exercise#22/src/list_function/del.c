#include <malloc.h>
#include "list_struct.h"

int del(struct list_drivers* list, pid_t pid, int* lenght){
    struct list_drivers* cur = list->next;
    for (int i = 0; i < *lenght; i++)
    {
            if(cur->pid_driver == pid){
                if((cur->next == 0) & (cur->lees == 0)){
                    *lenght = *lenght - 1;
                    break;
                }
                if(cur->lees == 0){
                    list->next = (cur->next);
                    cur->next->lees = 0;
                    *lenght = *lenght - 1;
                    free(cur);
                    break;
                }
                if(cur->next == 0){
                    cur->lees->next = 0;
                    *lenght = *lenght - 1;
                    free(cur);
                    break;
                }
                cur->lees->next = cur->next;
                cur->next->lees = cur->lees;
                *lenght = *lenght - 1;
                free(cur);
                break;
            }

        cur = cur->next;
    }
}