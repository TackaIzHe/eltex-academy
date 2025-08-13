#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int pid = 0;
    printf("Введите pid процеса\n");
    scanf("%d",&pid);
    kill(pid,SIGUSR1);

    exit(EXIT_SUCCESS);
}