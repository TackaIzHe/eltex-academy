#include <stdlib.h>
#include <signal.h>

void get_sigint(int i){
    return;
}

int main(){
    signal(2,get_sigint);
    while(1){

    }
    exit(EXIT_SUCCESS);
}