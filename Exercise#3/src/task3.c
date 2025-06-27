#include <stdio.h>

int task3(){
    int mass[10] = {1,2,3,4,5,6,7,8,9,10};
    int* nav = mass;

    printf("Задание №3\n");
    for(int i=0;i<sizeof(mass)/sizeof(int);i++){
        printf("%d ",*(nav+i));
    }
    printf("\n");


    return 0;
}