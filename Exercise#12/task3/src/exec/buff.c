#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "execProc.h"

int buff(char **atr, int lenght)
{
    if (lenght <= 0)
    {
        return 1;
    }
    char *binPath = malloc(15);
    strcat(binPath, "/bin/");
    strcat(binPath, atr[0]);
    execv(binPath, atr);
    free(binPath);
}