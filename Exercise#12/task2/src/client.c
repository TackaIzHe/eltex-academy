#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int des = open("pipe",O_RDONLY);
    char str[4];
    read(des,str,4);
    close(des);
    printf("%s\n",str);
    unlink("pipe");
    exit(EXIT_SUCCESS);
}