#include <stdio.h>
#include "main.h"

int log_func(struct thread_arg_struct* obj, int col, int shopNum){
    printf("Имя: %s, Номер магозина:%d, Остаток в магазине:%d, получил(погрузил): %d, Потребность: %d\n", obj->name, shopNum,obj->stores[0][shopNum], col, obj->potreb);
    return 0;
}