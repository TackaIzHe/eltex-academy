#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int find_pipe_line(char** cur, char*** buff){
    for(int i=0;cur[i]!=NULL;i++){
        if(!strcmp(cur[i],"|")){
            printf("%s\n",cur[i]);
        }
    }

}