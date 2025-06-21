#include <stdio.h>
#include "task.h"

int task2(){
    int x = 0;
    char binary[8];
    while(1)
    {
        printf("Задание№2\n");
        printf("Введите целое число от -128 до 127 включительно: ");
        scanf("%d",&x);
        if(x<127 || x>-129){
            break;
        }
    }
    if(x>=0){
        convert(x, binary);
    }
    else{
        x *= -1;
        convert(x, binary);
        notBinary(binary);
        plusOne(binary);
    }
    printf("%s \n",binary);
    return 0;
}