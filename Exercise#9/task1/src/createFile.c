#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int createFile(char* fileName){
    int des = 0;
    des = open(fileName, O_WRONLY | O_CREAT , 0666 );
    if(des == -1){
        printf("Ошибка создания файла\n");
        exit(EXIT_FAILURE);
    }
    des = close(des);
    if(des == -1){
        printf("Ошибка при закрытии файла");
    }
    return 0;

}