#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <sys/mman.h>
#include "list_function/list_func.h"
#include "menu_scren/menu.h"
#include "driver_function/sem_shm.h"


int main(){
    void* addr_shm;  
    sem_t* sem;
    struct list_drivers drivers;
    drivers.last = 0;
    drivers.lees = 0;
    drivers.next = 0;

    init_mman(drivers, &addr_shm, &sem);

    printf("help показывает список програм \n");
    printf("create_driver создаёт driver\n");
    printf("send_task <pid> <timer> отпровляет команду driver\n");
    printf("get_status <pid> показывает статус driver\n");
    printf("get_drivers отоброжает всех driver\n");
    printf("exit завершение програмы\n");

    menu(&addr_shm);
    close_mman(addr_shm, sem);
    exit(EXIT_SUCCESS);
}