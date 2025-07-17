#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int readFromFile(char* fileName, char* str , int lenght){
    int des = 0;
    int stat = 0;
    des = open(fileName,O_RDONLY);
    if(des == -1){
        printf("Ошибка открытия файла для чтения\n");
        exit(EXIT_FAILURE);
    }
    stat = read(des,str,lenght);
    if(stat == -1){
        printf("Ошибка при чтении файла");
    }
    stat = close(des);
    if(stat == -1){
        printf("Ошибка при закрытии файла");
    }
    return 0;
}