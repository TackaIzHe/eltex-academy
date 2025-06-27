#include <stdio.h>

int task1(void){
    int number = 0;
    int cvad = 0;
    printf("Задание №1 \n");
    printf("Введите число от 1 до 99: \n");
    scanf("%2d",&number);
    cvad = number*number;
    int n[number][number];
    
    int count =1;

    for(int i=0; i<number;i++){
        for(int j=0;j<number;j++){
            n[i][j] = count;
            count++; 
        }
    }

    for(int i=0; i<number;i++){
        for(int j=0;j<number;j++){
            printf("%d ",n[i][j]); 
        }
        printf("\n");
    }


    return 0;
}