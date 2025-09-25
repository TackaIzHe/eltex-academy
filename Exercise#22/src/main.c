#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "list_function/list_func.h"


int main(){
    struct list_drivers* drivers;
    int list_lenght = 0;
    drivers = malloc(sizeof(struct list_drivers));
    add(&drivers, 52, &list_lenght);
    add(&drivers, 512320, &list_lenght);
    add(&drivers, 5432, &list_lenght);
    add(&drivers, 52, &list_lenght);
    add(&drivers, 99, &list_lenght);
    add(&drivers, 51232, &list_lenght);
    add(&drivers, 52, &list_lenght);
    add(&drivers, 512, &list_lenght);
    add(&drivers, 52, &list_lenght);

    get_all(drivers, list_lenght);

    free(drivers);
    exit(EXIT_SUCCESS);
}