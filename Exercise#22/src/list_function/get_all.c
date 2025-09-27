#include <stdio.h>
#include <string.h>
#include "list_struct.h"

int get_all(struct list_drivers* list, int lenght){
    printf("\n");
    char space[10] = "_________";
    struct list_drivers* cur = list->next;
    for(int i=0;i<lenght;i++){
        int count=8;
        for(int j=10;j<=cur[0].pid_driver;j*=10){
            space[count] = '\0';
            count--;
        }
        printf("Pid: %d;%s", cur[0].pid_driver, space);
        printf("Status: %s\n", cur[0].status);
        strcpy(space,"_________");
        if(cur[0].next==0){
            break;
        }
        cur = cur[0].next;
    }
    printf("\n");
    return 0;
}