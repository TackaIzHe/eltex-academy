#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#define HANDLE_ERR(msg)\
    do{ perror(msg); exit(EXIT_FAILURE); } while(0)

#define SHM_PATH "/shm_file"
#define SEM_PATH "/sem_file"
#define SHM_LENGHT 1024

int main(){
    sem_t* sem;
    int fd;
    void* addr_shm;       

    fd = shm_open(SHM_PATH, O_RDWR, 0666);
    if(fd == -1){
        HANDLE_ERR("shm_open err");
    }
    sem = sem_open(SEM_PATH, O_RDWR, 0666);
    if(sem == SEM_FAILED){
        HANDLE_ERR("sem_open err");
    }

    addr_shm = mmap(NULL, SHM_LENGHT, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr_shm == MAP_FAILED){
        HANDLE_ERR("mmap err");
    }

    printf("%s\n", addr_shm);
    strcpy(addr_shm, "Hello!");
    sem_post(sem);


    if( munmap(addr_shm, SHM_LENGHT) == -1){
        HANDLE_ERR("munmap err");
    }

    if( sem_close(sem) == -1){
        HANDLE_ERR("sem_close err");
    }

    exit(EXIT_SUCCESS);
}