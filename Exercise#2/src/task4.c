#include <stdio.h>

int task4(){
    int number = 0;
    int count = 1;
    printf("Задание №4 \n");
    printf("Введите число от 0 до 99:");
    scanf("%2d",&number);
    int n[number][number];
    int cvad = number*number;

    for(int i=1;count<cvad-1;i++){
        for(int j=i-1;j<number-i;j++){
            n[i-1][j] =count;
            count++;
        }
        for(int j=i-1;j<number-i;j++){
            n[j][number-i] =count;
            count++;
        }
        for(int j=number - i; j > 0 + i-1;j--){
            n[number - i][j] =count;
            count++;
        }
        for(int j=number - i; j > 0 + i - 1;j--){
            n[j][i-1] =count;
            count++;
        }
        
    }
    if(number & 1){
        n[number/2][number/2] = cvad;
    }

    for(int i=0;i<number;i++){
        for(int j = 0; j<number;j++){
            printf("%d ",n[i][j]);
        }
        printf("\n");
    }


    return 0;
}