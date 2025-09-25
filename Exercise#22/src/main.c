#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "list_function/list_func.h"


int main(){
    struct list_drivers* drivers;
    int list_lenght = 0;
    drivers = malloc(sizeof(struct list_drivers));
    for(int i=0;i<100;i++){
        add(drivers, 52+i, &list_lenght);
    }
    del(drivers,100,&list_lenght);
    del(drivers,100,&list_lenght);
    get_all(drivers, list_lenght);

    free_list(drivers);
    exit(EXIT_SUCCESS);
}