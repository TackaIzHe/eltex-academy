#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "list_function/list_func.h"
#include "menu_scren/menu.h"


int main(){
    struct list_drivers* drivers;
    drivers = malloc(sizeof(struct list_drivers));
    
    menu(drivers);
    
    free_list(drivers);
    exit(EXIT_SUCCESS);
}