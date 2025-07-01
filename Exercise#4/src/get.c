#include "stract.h"
#include <stdio.h>

int get(struct abonent mass){
    printf("Имя: %s\n",mass.name);
    printf("Фамилия: %s\n",mass.second_name);
    printf("Телефон: %s\n",mass.tel);
    printf("\n");

    return 0;
}