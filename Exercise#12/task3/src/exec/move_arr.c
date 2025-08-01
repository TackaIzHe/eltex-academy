#include <stdlib.h>
#include <stdio.h>

int move_arr(char*** arr, int* ind){
    int count=0;
    for(int i=1;arr[0][i+*ind]!=NULL;i++){
        arr[0][i-1] = arr[0][i+*ind];
        count++;
    }
    *ind = count;
    arr[0][count] = NULL;
}