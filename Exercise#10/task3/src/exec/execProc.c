#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

int execProc(char** atr,int lenght){
    pid_t proc;
    char* binPath = malloc(6);
    strcat(binPath,"/bin/");

    strcat(binPath,atr[0]);
    proc = fork();
    if(proc == 0){
        execl(binPath,atr[0],atr[1],atr[2],NULL);
        exit(EXIT_SUCCESS);
    }
    return 0;
}