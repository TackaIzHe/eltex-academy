#include <stdio.h>
#include "main.h"
#include "stract.h"

int search(struct abonent *mass, int length){
    char name[10] = {0,0,0,0,0,0,0,0,0,0};
    printf("Введите имя: \n");
    scanf("%10s",name);
    printf("\nНайденые записи: \n");
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(mass[i].name[j] == 0 && name[j] == 0){
                get(mass[i]);
                break;
            }
            else if(mass[i].name[j] = name[j]){
                continue;
            }
            break;
            
        }
        
    }
    return 0;

}