#include <stdio.h>
#include "../list_function/list_func.h"
#include "../driver_function/sem_shm.h"

int get_drivers(void** addr_shm){
    reopen_shm(addr_shm);
    struct list_drivers* start = (struct list_drivers*)(*addr_shm + 4);
    get_all(start,*(int*)*addr_shm);
}