#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "thread_arg_struct.h"

int init_thread_obj(struct thread_arg_struct*** obj, int colBuyer, int colLoader, int** store, int** busy){
    srand(time(NULL));
    for(int i=1;i<=colBuyer;i++){
        (*((*obj)+i-1)) = realloc((*((*obj)+i-1)), sizeof(struct thread_arg_struct) * (i+1));
        char name[30] = "Покупатель ";
        char count[2] = "0"; 
        count[0] = count[0]+i ;
        strcat(name,count);
        strcpy((*((*obj)+i-1))->name,name);
        (*((*obj)+i-1))->potreb = 90000+rand()%10000;
        (*((*obj)+i-1))->stores = store;
        (*((*obj)+i-1))->busy = busy;
    }

    for(int i=1;i<=colLoader;i++){
        (*((*obj)+i+colBuyer-1)) = realloc((*((*obj)+i+colBuyer-1)), sizeof(struct thread_arg_struct) * (i+1));
        char name[30] = "Погружчик ";
        char count[2] = "0"; 
        count[0] = count[0]+i ;
        strcat(name,count);
        strcpy((*((*obj)+i+colBuyer-1))->name,name);
        (*((*obj)+i+colBuyer-1))->potreb = 90000+rand()%10000;
        (*((*obj)+i+colBuyer-1))->stores = store;
        (*((*obj)+i+colBuyer-1))->busy = busy;
    }
    
    return 0;
}