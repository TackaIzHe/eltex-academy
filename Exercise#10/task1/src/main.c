#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    pid_t child_pid;
    int status;
    child_pid = fork();
    if(child_pid == 0){
        printf("Child pid: %d\n",getpid());
        printf("Child ppid: %d\n",getppid());
        exit(EXIT_SUCCESS);
    }else{
        printf("Parent pid: %d\n",getpid());
        printf("Parent ppid: %d\n",getppid());
        wait(&status);
        printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    exit(EXIT_SUCCESS);
}