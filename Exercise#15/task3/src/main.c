#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void i(int){

}

int main(){
    sigset_t s;
    int sig = 0;

    signal(SIGUSR1,i);

    sigemptyset(&s);
    sigaddset(&s,SIGUSR1);
    while(1){
        sigwait(&s,&sig);
        printf("Получен сигнал SIGUSR1\n");
    }
    exit(EXIT_SUCCESS);
}