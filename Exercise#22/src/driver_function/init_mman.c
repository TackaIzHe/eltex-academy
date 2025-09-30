#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sem_shm.h"

int init_mman(struct list_drivers list, void** addr_shm){

    int fd;

    fd = shm_open(SHM_PATH, O_CREAT | O_RDWR, 0666);
    if(fd == -1){
        perror("shm_open err");
    }

    if( ftruncate(fd, SHM_LENGHT) == -1){
        perror("ftruncate err");
    }

    *addr_shm = mmap(NULL, SHM_LENGHT, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(*addr_shm == MAP_FAILED){
        perror("mmap err");
    }
    *(int*)(*addr_shm) = 0;
    void * list_start = ((*addr_shm)+4);
    *(struct list_drivers*)list_start = list;
}