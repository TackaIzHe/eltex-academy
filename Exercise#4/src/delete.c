#include <stdio.h>

int delet(int* length){
    if(*length == 0){
        printf("В справочнике нет записей\n");
        return 0;
    }
    *length = *length - 1;
    return 0;
}