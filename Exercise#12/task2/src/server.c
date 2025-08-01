#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int res = mkfifo("pipe", 0666);
    if(res < 0){
        printf("Ошибка создания FIFO\n");
        exit(EXIT_FAILURE);
    }
    int des = open("pipe",O_WRONLY);
    write(des,"Hi!",4);
    close(des);
    exit(EXIT_SUCCESS);
}