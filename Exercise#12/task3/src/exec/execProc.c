#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "execProc.h"

int execProc(char ***atr, int lenght)
{
    if (lenght <= 0)
    {
        return 1;
    }
    pid_t proc;
    char *binPath = malloc(15);
    strcat(binPath, "/bin/");

    strcat(binPath, atr[0][0]);
    proc = fork();
    if (proc == 0)
    {
        execv(binPath, *atr);
        free(binPath);
        exit(EXIT_SUCCESS);
    }
    return 0;
}