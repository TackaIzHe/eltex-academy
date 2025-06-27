#include <stdio.h>

int task3(){
    int number =0;
    int count = 1;

    printf("Задание №3 \n");
    printf("Введите число от 0 до 99:");
    scanf("%2d",&number);
    int n[number][number];

    for (int i = 0; i < number; i++)
    {
        for(int j = 0; j < number; j++){
            n[i][j] = 1;
        }
        
    }

    for (int i = 0; i < number; i++)
    {
        for(int j = count; j < number; j++){
            n[i][j - count] = 0;
        }
        count++;
    }

    for (int i = 0; i < number; i++)
    {
        for(int j = 0; j < number; j++){
            printf("%d ",n[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}