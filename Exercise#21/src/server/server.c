#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void sigint(int i){
    printf("asd%d\n",i);
    exit(EXIT_SUCCESS);
}

int main(){
    sigset_t s;
    int sig =0;
    signal(SIGINT, sigint);
    sigwait(&s, &sig);
    
}