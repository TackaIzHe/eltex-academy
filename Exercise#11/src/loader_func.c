#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "main.h"

void* loader_func(void* arg){
    struct thread_arg_struct* obj = (struct thread_arg_struct*)arg;
    srand(time(NULL));
    while(obj->potreb>0){
        int selectShop = rand() % 5;
        if(obj->busy[0][selectShop] == 0 ){
            obj->busy[0][selectShop] = 1;
            obj->stores[0][selectShop] += 10000;
            log_func(obj,10000,selectShop);
            sleep(1);
            obj->busy[0][selectShop] = 0;
        }
    }
    return 0;
}