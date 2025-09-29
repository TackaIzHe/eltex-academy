#include <unistd.h>
#include <stdio.h>

int send_task(pid_t pid, int timer, int* lenght){
    printf("%d %d\n",pid, timer);
}   