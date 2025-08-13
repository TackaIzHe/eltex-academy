#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void print_mess(int i){
    printf("Сигнал получен\n");
}


int main(){
    signal(10,print_mess);
    while(1){
        
    }
    exit(EXIT_SUCCESS);
}