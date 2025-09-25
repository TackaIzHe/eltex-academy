#include <stdio.h>
#include <string.h>
#include "list_struct.h"

int get_all(struct list_drivers* list, int lenght){
    printf("\n");
    char space[10] = "_________";
    for(int i=0;i<lenght;i++){
        int count=8;
        for(int j=10;j<list[i].pid_driver;j*=10){
            space[count] = '\0';
            count--;
        }
        printf("Pid: %d;%s", list[i].pid_driver, space);
        printf("Status: %s \n", list[i].status);
        strcpy(space,"_________");
    }
    printf("\n");
    return 0;
}