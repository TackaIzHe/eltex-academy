#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "proc.h"

int main(){
    int status1;
    int status2;
    pid_t child_pid1;
    pid_t child_pid2;
    child_pid1 = fork();
    if(child_pid1 == 0){
        int status3;
        int status4;
        pid_t child_pid3;
        pid_t child_pid4;
        child_pid3 = fork();
        if(child_pid3 == 0){
            proc("task3",getpid(),getppid());
            exit(EXIT_SUCCESS);    
        }
        child_pid4 = fork();
        if(child_pid4 == 0){
            proc("task4",getpid(),getppid());
            exit(EXIT_SUCCESS);    
        }
        proc("task1",getpid(),getppid());
        wait(&status3);
        wait(&status4);
        exit(EXIT_SUCCESS);
    }
    child_pid2 = fork();
    if(child_pid2 == 0){
        int status5;
        pid_t child_pid5;
        child_pid5 = fork();
        if(child_pid5 == 0){
            proc("task5",getpid(),getppid());
            exit(EXIT_SUCCESS);    
        }
        proc("task2",getpid(),getppid());
        wait(&status5);
        exit(EXIT_SUCCESS);
    }
    proc("main",getpid(),getppid());
    wait(&status1);
    wait(&status2);
    exit(EXIT_SUCCESS);
}