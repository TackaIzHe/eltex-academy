#include "stract.h"
#include "main.h"
#include <stdio.h>

int exitMain(int *isWork);
int printMenu(int* sel);

int main(){
    struct abonent mass[100];
    int length = 0;
    int isWork = 1;
    int sel = 0;
    while(isWork){
        printMenu(&sel);
        switch (sel)
        {
        case 1:
            add(mass, &length);
            break;
        case 2:
            delet(&length);
            break;
        case 3:
            search(mass, length);
            break;
        case 4:
            getAll(mass, length);
            break;
        case 5:
            exitMain(&isWork);
            break;
        
        default:
            printf("%d ",sel);
            printf("Нет такого действия\n");
            break;
        }
    }
    return 0;
}

int printMenu(int* sel){
    printf("1) Добавить абонента\n");
    printf("2) Удалить абонента\n");
    printf("3) Поиск абонентов по имени\n");
    printf("4) Вывод всех записей\n");
    printf("5) Выход\n");
    scanf("%d",sel);
    return 0;
}

int exitMain(int* isWork){
    *isWork = 0;
    return 0;
}