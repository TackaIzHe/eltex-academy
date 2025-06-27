#include <stdio.h>

int task4(){
    char str[10];
    char subStr[5];
    int n =0;
    int* index = &n;
    int count = 0;
    printf("Задание №4 \n");
    printf("Введите строку длиной 9:");
    scanf("%9s",str);
    printf("Введите подстроку длиной 4:");
    scanf("%4s",subStr);
    str[9]='\0';
    subStr[4]='\0';
    
    for(int i=0;i<9; i++){
        if(count == 4){
            *index = i - count;
            break;
        }
        else if(subStr[count] == str[i]){
            count++;
            
        }
        else if(subStr[count] != str[i]){
            if(count>0){
                i--;
            }
            count = 0;
            
        }
    }
    printf("%d \n",*index);

    return 0;
}