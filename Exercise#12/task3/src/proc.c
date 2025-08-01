#include "splitFunc/split.h"
#include "exec/execProc.h"
#include <sys/wait.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int proc(char *comand)
{
    int status = 0;
    char **atr;
    atr = malloc(8);

    int atrLenght = 0;

    split(comand, &atr, &atrLenght);
    atr = realloc(atr, (atrLenght + 1) * 8);
    atr[atrLenght] = malloc(4);
    atr[atrLenght] = NULL;

    int ind_pipe;
    int res = find_pipe_line(&atr, &ind_pipe);
    if (res)
    {
        pid_t proc1;
        int des = mkfifo("pipe", 0666);
        proc1 = fork();
        if(proc1 == 0){
            int fd = open("pipe", O_WRONLY);
            int new_fd = dup2(fd, 1);
            buff(atr,atrLenght);
            close(fd);
            close(new_fd);
            exit(EXIT_SUCCESS);
        }
        pid_t proc2;
        proc2 = fork();
        if(proc2 == 0){

            int fd = open("pipe", O_RDONLY);
            int new_fd = dup2(fd, 0);\
            move_arr(&atr, &ind_pipe);
            // buff(atr,ind_pipe);
            execProc(&atr,ind_pipe);
            int s;
            wait(&s);
            close(new_fd);
            unlink("pipe");
            exit(EXIT_SUCCESS);
        }
    }
    else
    {
        execProc(&atr, atrLenght);
    }

    wait(&status);
    free(atr);
    return 0;
}