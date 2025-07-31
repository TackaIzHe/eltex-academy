#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "stdio.h"

void* buyer_func(void* arg){
    struct thread_arg_struct* obj = (struct thread_arg_struct*)arg;
    srand(time(NULL));
    while(obj->potreb>0){
        int selectShop = rand() % 5;
        if(obj->busy[0][selectShop] == 0 ){
            obj->busy[0][selectShop] = 1;
            if(obj->stores[0][selectShop]>=5000){
                if(obj->potreb<5000){
                    obj->stores[0][selectShop] -= obj->potreb;        
                    obj->potreb = 0;
                    log_func(obj, obj->potreb,selectShop);
                    continue;
                }
                obj->potreb -= 5000;
                obj->stores[0][selectShop] -= 5000;
                log_func(obj, 5000,selectShop);
            }
            else{
                obj->potreb -= obj->stores[0][selectShop];
                int ost = obj->stores[0][selectShop];
                obj->stores[0][selectShop] = 0;
                log_func(obj, ost,selectShop);
            }
            sleep(2);
            obj->busy[0][selectShop] = 0;
        }
    }
    return 0;
}