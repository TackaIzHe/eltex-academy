#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int writeToFile(char* fileName, char* str , int lenght){
    int des = 0;
    int stat = 0;
    des = open(fileName,O_WRONLY);
    if(des == -1){
        printf("Ошибка записи в файл\n");
        perror("Требуються права на запись");
        exit(EXIT_FAILURE);
    }
    stat = write(des,str,lenght);
    if(stat == -1){
        printf("Ошибка при записи в файл");
    }
    stat = close(des);
    if(stat == -1){
        printf("Ошибка при закрытии файла");
    }
    return 0;
}