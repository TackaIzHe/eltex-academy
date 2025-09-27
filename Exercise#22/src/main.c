#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "list_function/list_func.h"
#include "driver_function/driver_func.h"
#include "menu_scren/menu.h"


int main(){
    struct list_drivers* drivers;
    int list_lenght = 0;
    drivers = malloc(sizeof(struct list_drivers));
    

    menu();
    
    
    free_list(drivers);
    exit(EXIT_SUCCESS);
}