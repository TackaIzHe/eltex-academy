#include <stdio.h>
#include "task.h"

int task4(){
    int x = 0;
    unsigned int y = 0;
    char intBinary[33];
    char binary[9];
    intBinary[32]= '\0';
    binary[8] = '\0';
    while(1)
    {
        printf("Задание№4\n");
        printf("Введите целое положительное число: ");
        scanf("%d",&x);
        printf("Введите целое положительное число от 0 до 255 включительно: ");
        scanf("%d",&y);
        if(y < 256){
            if(x > -1){
                break;
            }
        }
    }
    convert(x,intBinary,31);
    convert(y, binary,7);
    
    replaceBinary(16,intBinary,binary);
    printf("%s \n",intBinary);
    printf("%d \n",deconvert(intBinary,31));
    return 0;
}