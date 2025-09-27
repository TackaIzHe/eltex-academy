#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int menu(){
    char buff[256];  
    char *lex[3];  
    int lex_counter = 0;
    
    scanf("%255[^\n]",buff);

    char *token = strtok(buff, " ");
    while ((token != NULL) && (lex_counter < 3)) {
        lex[lex_counter] = token;  
        lex_counter++;
        token = strtok(NULL, " ");  
    }
    
}