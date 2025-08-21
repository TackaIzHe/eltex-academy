#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_err(msg)\
do{ perror(msg); exit(EXIT_FAILURE);}while(0)

int main(){
    key_t key;
    int fd;
    int shm;
    void* ukazatel;
    shm = open("shm", O_CREAT, 0666);
    if(shm == -1){
        handle_err("open err");
    }
    close(shm);

    key = ftok("shm", 1);
    if(key == -1){
        handle_err("ftok err");
    }
    fd = shmget(key, 1, 0666 | IPC_CREAT);
    if(fd == -1){
        handle_err("shmget err");
    }
    ukazatel = shmat(fd, 0, O_RDWR);
    if(ukazatel == (void*)-1){
        handle_err("shmat err");
    }
    strcpy(ukazatel, "Hi!");

    while(strcmp(ukazatel,"Hi!") == 0);
    printf("%s\n",ukazatel);
    
    shmdt(ukazatel);
    unlink("shm");

    exit(EXIT_SUCCESS);
}