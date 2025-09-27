#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int init_driver(){
    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0){
        printf("%d\n", getpid());
    }else{
        wait(&status);
        printf("%d\n", getpid());
        return 0;   
    }
}