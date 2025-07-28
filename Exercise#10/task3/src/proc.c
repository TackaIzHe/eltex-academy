#include "splitFunc/split.h"
#include "exec/execProc.h"
#include <sys/wait.h>
#include <malloc.h>

int proc(char *comand)
{
    int status = 0;
    char **atr;
    atr = malloc(8);

    int atrLenght = 0;

    split(comand, &atr, &atrLenght);
    execProc(atr, atrLenght);
    wait(&status);
    // free(atr);
    return 0;
}