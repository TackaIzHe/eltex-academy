#include <stdio.h>
#include "list_function/list_func.h"
#include "comand_function/comand_func.h"

int kill_child_proc(void** addr_shm){
    struct list_drivers* start = (struct list_drivers*)(*addr_shm + 4);
    struct list_drivers* cur = start->next;
    while(1){
        if(cur == 0){
            break;
        }
        send_comand(cur->pid_driver,"exit");
        cur = cur->next;
    }
}