//масив 5 int заполнить случайными числами в пределах 10000
//породить 3 потока покупателей потребность в пределах 100000
// если в магазине есть покупатель то другие немогут туда попасть 
// засыпает на 2с 
// при удовлетворении потребности завершаеться поток покупателя
// создать поток погружчика 
//погружает по 10000 в свободный магазин 
// засыпает на 1с
//програма завершаеться как все покупатели удовлетворили потребность

#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include "thread_arg_struct.h"
#include <malloc.h>
#include "main.h"

int WorkLoader = 1; 

int main(){
    srand(time(NULL));
    int* store;
    int* busy;
    int threadLenght = 4 ;
    struct thread_arg_struct** obj;
    obj = malloc(8*threadLenght);
    pthread_t buyer1, buyer2, buyer3;
    pthread_t loader;
    store = malloc(sizeof(int)*5);
    busy = malloc(sizeof(int)*5);
    for(int i =0; i< 5;i++){
        store[i] = 9000 + rand() % 1000;
    }
    init_thread_obj(&obj,3,1, &store, &busy);
    pthread_create(&buyer1,NULL,buyer_func,obj[0]);
    pthread_create(&buyer2,NULL,buyer_func,obj[1]);
    pthread_create(&buyer3,NULL,buyer_func,obj[2]);
    pthread_create(&loader,NULL,loader_func,obj[3]);
    pthread_join(buyer1,NULL);
    pthread_join(buyer2,NULL);
    pthread_join(buyer3,NULL);
    WorkLoader = 0;
    pthread_exit(NULL);
    for(int i=0;i<threadLenght;i++){
        free(obj[i]);
    }
    free(obj);
    free(store);
    free(busy);
    exit(EXIT_SUCCESS);
}