#include <stdio.h>
#include <string.h>
#include "../comand_function/comand_func.h"

int menu(){
    
    char buff[256];  
    char *lex[3];  
    int lex_counter = 0;
    
    while(1){
        scanf("%255[^\n]",buff);
        
        char *token = strtok(buff, " ");
        while ((token != NULL) && (lex_counter < 3)) {
            lex[lex_counter] = token;  
            lex_counter++;
            token = strtok(NULL, " ");  
        }
        if(strcmp(lex[0],"create_driver")){

        }else if(strcmp(lex[0],"send_task")){ //<pid><timer>

        }else if(strcmp(lex[0],"get_status")){ //<pid>

        }else if(strcmp(lex[0],"get_drivers")){

        }else if(strcmp(lex[0],"del_driver")){ //<pid>

        }

    }
    
}