#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int find_pipe_line(char*** cur, int* ind){
    for(int i=0;cur[0][i]!=NULL;i++){
        if(!strcmp(cur[0][i],"|")){
            *ind = i;
            cur[0][i] = NULL;
            return 1;
        }
    }
    return 0;
}