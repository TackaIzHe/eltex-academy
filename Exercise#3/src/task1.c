#include <stdio.h>

int task1(){
    int num = 0;
    int chr = 0;
    int* number = &num;
    int* bait = &chr;
    unsigned char* hex = (unsigned char*)number;

    printf("Задание №1 \n");
    printf("Введите число: ");
    scanf("%d",number);

    printf("Введите число от 0 до 255: ");
    scanf("%3d",bait);
    if(*bait>255){
        *bait = 255;
    }
    else if(*bait<0){
        *bait = 0;
    }
    printf("%p \n",*number);
    *(hex+2) = (unsigned char)*bait;
    printf("%p \n",*number);
    
    return 0;
}