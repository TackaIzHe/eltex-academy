#include <stdio.h>
#include "task.h"

int task3(){
    unsigned int x = 0;
    char binary[8];
    while(1)
    {
        printf("Задание№3\n");
        printf("Введите целое положительное число от 0 до 255 включительно: ");
        scanf("%d",&x);
        if(x<256){
            break;
        }
    }
    convert(x, binary, 7);
    int result = countOne(binary);
    printf("%d - %s \n",result,binary);
    return 0;
}