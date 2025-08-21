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
    void* ukazatel;
 
    key = ftok("shm", 1);
    if(key == -1){
        handle_err("ftok err");
    }
    fd = shmget(key, 1, 0666);
    if(fd == -1){
        handle_err("shmget err");
    }
    ukazatel = shmat(fd, 0, O_RDWR);
    if(ukazatel == (void*)-1){
        handle_err("shmat err");
    }

    printf("%s\n", ukazatel);

    strcpy(ukazatel, "Hello!");
    shmdt(ukazatel);

    exit(EXIT_SUCCESS);
}