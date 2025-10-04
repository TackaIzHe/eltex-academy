#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../socket_func.h"

int socket_fd = 0;
int pid = 0;

void sigint(int){
    if(pid != getpid()){
/// ОТПРОВЛЯТЬ КОИЕНТАМ СООБЩЕНИЕ О ВЫКЛЮЧЕНИИ СЕРВЕРА
    }
    else{
        close(socket_fd);
    }
    exit(EXIT_SUCCESS);
}

int main(){
    signal(SIGINT, sigint);
    pid = getpid();
    open_socket(&socket_fd);
    
}