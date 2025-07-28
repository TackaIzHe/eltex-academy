#include <stdio.h>
#include <string.h>
#include <malloc.h>

int split(char* str, char*** atr, int* atrLenght){
    int lenght = 0;
    int prevInd = 0;
    strcat(str," ");
    lenght = strlen(str);
    for(int i=0;i<lenght;i++){
        if(str[i]==' '){
            *atrLenght = *atrLenght + 1;
            *(atr) = realloc(*(atr),*atrLenght*8);
            *(*(atr)+*atrLenght-1) = malloc(i+1 - prevInd);
            for(int j=prevInd;j<i;j++){
                *(*(*(atr)+*atrLenght-1)+j-prevInd) = str[j];
            }
            *(*(*(atr)+*atrLenght-1)+i+1 - prevInd) = '\0';
            prevInd = i+1;
        }
    }
    return 0;
}