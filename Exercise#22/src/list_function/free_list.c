#include <malloc.h>
#include "list_struct.h"

int free_list(struct list_drivers* list){
    struct list_drivers* cur = list;
    struct list_drivers* last;
    while(1){
        if(cur == 0){
            free(last);
            break;
        }
        if(cur->lees != 0)
        free(cur->lees);
        last = cur;
        cur = cur->next;
    }
    
}