#include "stract.h"
#include "main.h"
#include <stdio.h>

int getAll(struct abonent *mass, int length){
    printf("Весь справочник: %d\n",length);
    for (int i = 0; i < length; i++)
    {
        get(mass[i]);
    }
    
    return 0;
}