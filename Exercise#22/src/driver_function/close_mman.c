#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "sem_shm.h"

int close_mman(void* addr_shm){
    if( munmap(addr_shm, SHM_LENGHT) == -1){
        perror("munmap err");
    }

    if( shm_unlink(SHM_PATH) == -1){
        perror("shm_unlink err");
    }

}