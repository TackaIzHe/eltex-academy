#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

int execProc(char** atr,int lenght){
    if(lenght<=0){
        return 1;
    }
    pid_t proc;
    char* binPath = malloc(6);
    strcat(binPath,"/bin/");

    strcat(binPath,atr[0]);
    atr = realloc(atr,(lenght+1) * 8);
    atr[lenght] = malloc(4);
    atr[lenght] = NULL;
    proc = fork();
    if(proc == 0){
        execv(binPath, atr);
        free(binPath);
        exit(EXIT_SUCCESS);
        
    }
    return 0;
}