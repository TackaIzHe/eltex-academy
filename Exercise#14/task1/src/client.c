#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_err(msg)\
do{ perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    key_t key_shm, key_sem;
    int fd_shm, fd_sem;
    void* ukazatel;
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;

    key_shm = ftok("shm", 1);
    if(key_shm == -1){
        handle_err("ftok_shm err");
    }

    key_sem = ftok("shm", 2);
    if(key_sem == -1){
        handle_err("ftok_sem err");
    }

    fd_shm = shmget(key_shm, 1, 0666);
    if(fd_shm == -1){
        handle_err("shmget err");
    }

    fd_sem = semget(key_sem, 1, 0666);
    if(fd_sem == -1){
        handle_err("semget err");
    }

    ukazatel = shmat(fd_shm, 0, 0);
    if(ukazatel == (void*)-1){
        handle_err("shmat err");
    }

    printf("%s\n", ukazatel);

    strcpy(ukazatel, "Hello!");
    semop(fd_sem, &buf, 1);
    shmdt(ukazatel);

    exit(EXIT_SUCCESS);
}