#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "sem_shm.h"

int reopen_shm(void** addr_shm){
    int fd;

    fd = shm_open(SHM_PATH, O_RDWR, 0666);
    if(fd == -1){
        perror("shm_open err");
    }

    *addr_shm = mmap(NULL, SHM_LENGHT, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(*addr_shm == MAP_FAILED){
        perror("mmap err");
    }
    return 0;
}