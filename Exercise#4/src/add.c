#include "stract.h" 
#include <stdio.h>

int add(struct abonent *mass, int *length){
    if(*length == 100){
        printf("В справочнике нет места\n");
        return 0;
    }
    for(int i=0;i<10;i++){
        mass[*length].name[i] = 0;
        mass[*length].second_name[i] = 0;
        mass[*length].tel[i] = 0;
    }
    printf("Введите имя\n");
    scanf("%10s",mass[*length].name);
    printf("Введите фамилию\n");
    scanf("%10s",mass[*length].second_name);
    printf("Введите телефон\n");
    scanf("%10s",mass[*length].tel);
    *length = *length + 1;
    return 0;
}