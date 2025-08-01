#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int menu(){
    char comand[256];
    while(1){
        scanf(" %255[^\n]",comand);
        if(strcmp(comand, "exit") == 0){
            break;
        }
        proc(comand);
    }
    return 0;
}