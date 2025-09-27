#include "list_struct.h"

void* get(struct list_drivers* list, pid_t pid, int lenght){
    struct list_drivers* cur = list->next;
    for (int i = 0; i < lenght; i++)
    {
        if(cur->pid_driver == pid){
            return cur;
        }
        cur = cur->next;
    }
    
}