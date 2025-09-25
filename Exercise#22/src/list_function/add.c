#include <malloc.h>
#include <string.h>
#include "list_struct.h"

int add(struct list_drivers** list , pid_t pid, int* lenght){
    *list = realloc(*list,sizeof(struct list_drivers) * (*lenght+1));
    
    list[0][*lenght].pid_driver = pid;
    strcpy(list[0][*lenght].status,"Available") ;
    *lenght = *lenght + 1;
    return 0;
}