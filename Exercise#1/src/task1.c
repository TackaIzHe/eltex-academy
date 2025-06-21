#include <stdio.h>
#include "task.h"

int task1(){
    unsigned int x = 0;
    char binary[8];
    while(1)
    {
        printf("Задание№1\n");
        printf("Введите целое положительное число от 0 до 255 включительно: ");
        scanf("%d",&x);
        if(x < 256){
            break;
        }
    }
    convert(x, binary,7);
    printf("%s \n",binary);
    return 0;
}