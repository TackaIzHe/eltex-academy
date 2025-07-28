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
    proc = fork();
    if(proc == 0){
        execl(binPath,
            lenght>=0?atr[0]:NULL,
            lenght>=1?atr[1]:NULL,
            lenght>=2?atr[2]:NULL,
            lenght>=3?atr[3]:NULL,
            lenght>=4?atr[4]:NULL,
            lenght>=5?atr[5]:NULL,
            lenght>=6?atr[6]:NULL,
            lenght>=7?atr[7]:NULL,
            lenght>=8?atr[8]:NULL,
            lenght>=9?atr[9]:NULL,
            lenght>=10?atr[10]:NULL,
            NULL);
        free(binPath);
        exit(EXIT_SUCCESS);
        
    }
    return 0;
}