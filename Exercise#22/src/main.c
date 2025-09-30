#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <sys/mman.h>
#include "list_function/list_func.h"
#include "menu_scren/menu.h"
#include "driver_function/sem_shm.h"

int main(){
    struct list_drivers* drivers;
    drivers = malloc(sizeof(struct list_drivers));

    menu(drivers);

    if( munmap(addr_shm, SHM_LENGHT) == -1){
        perror("munmap err");
    }

    if( sem_close(sem) == -1){
        perror("sem_close err");
    }

    if( shm_unlink(SHM_PATH) == -1){
        perror("shm_unlink err");
    }

    if( sem_unlink(SEM_PATH) == -1){
        perror("sem_unlink err");
    }
 

    free_list(drivers);
    exit(EXIT_SUCCESS);
}