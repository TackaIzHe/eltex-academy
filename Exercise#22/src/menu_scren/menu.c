#include <stdio.h>
#include <string.h>
#include "../convert/convert.h"
#include "../comand_function/comand_func.h"

int menu(struct list_drivers* list){  
    int list_lenght = 0;
    char start_lex_word[1] = "";  
    char buff[256];  
    char *lex[3];  

    while(1){
        int lex_counter = 0;
        memset(buff, 0, 255);
        lex[1] = start_lex_word;
        lex[2] = start_lex_word;
        
        fgets(buff, 255, stdin);
        
        char *token = strtok(buff, " \t\n");
        while ((token != NULL) && (lex_counter < 3)) {
            lex[lex_counter] = token;  
            lex_counter++;
            token = strtok(NULL, " \t\n");  
        }

        if(strcmp(lex[0],"create_driver") == 0){
            create_driver(list, &list_lenght);
            list_lenght++;
            continue;
        }
        else if(strcmp(lex[0],"send_task") == 0){ //<pid><timer>
            if( (strcmp(lex[1],"") == 0) || (strcmp(lex[2],"") == 0)){
                printf("Укажите pid и task_time\n");
                continue;
            }
            int pid =0;
            int timer =0;
            convert_char_to_int(lex[1],&pid);
            convert_char_to_int(lex[2],&timer);
            send_task(pid, timer, &list_lenght);
            continue;
        }
        else if(strcmp(lex[0],"get_status") == 0){ //<pid>
            if(strcmp(lex[1],"") == 0){
                printf("Укажите pid\n");
                continue;
            }
            int pid =0;
            convert_char_to_int(lex[1],&pid);
            get_status(pid, &list_lenght);
            continue;
        }
        else if(strcmp(lex[0],"get_drivers") == 0){
            get_drivers(list, &list_lenght);
            continue;
        }
        else if(strcmp(lex[0],"del_driver") == 0){ //<pid>
            if(strcmp(lex[1],"") == 0){
                printf("Укажите pid\n");
                continue;
            }
            int pid =0;
            convert_char_to_int(lex[1],&pid);
            del_driver(pid, &list_lenght);
            continue;
        }
        else if(strcmp(lex[0],"help") == 0){
            printf("help показывает список програм \n");
            printf("create_driver создаёт driver\n");
            printf("send_task <pid> <timer> отпровляет команду driver\n");
            printf("get_status <pid> показывает статус driver\n");
            printf("get_drivers отоброжает всех driver\n");
            printf("del_driver <pid> удаляет driver\n");
            printf("exit завершение програмы\n");
            continue;
        }
        else if(strcmp(lex[0],"exit") == 0){
            break;
        }
        printf("Нет такой команды\n");

    }
    
}