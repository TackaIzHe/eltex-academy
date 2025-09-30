#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sem_shm.h"

void* addr_shm;  
sem_t* sem;

int init_mman(){

    int fd;

    fd = shm_open(SHM_PATH, O_CREAT | O_RDWR, 0666);
    if(fd == -1){
        perror("shm_open err");
    }
    sem = sem_open(SEM_PATH, O_CREAT | O_RDWR, 0666, 0);
    if(sem == SEM_FAILED){
        perror("sem_open err");
    }

    if( ftruncate(fd, SHM_LENGHT) == -1){
        perror("ftruncate err");
    }

    addr_shm = mmap(NULL, SHM_LENGHT, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr_shm == MAP_FAILED){
        perror("mmap err");
    }

    strcpy((char*)addr_shm, "Hi!");
    sem_wait(sem);
    printf("%s\n", addr_shm);

}