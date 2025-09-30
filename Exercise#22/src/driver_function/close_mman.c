#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "sem_shm.h"

int close_mman(void* addr_shm, sem_t* sem){
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
}