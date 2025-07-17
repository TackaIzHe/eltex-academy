#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(){
    char filename[11] = "output.txt";
    char mass[17] = "String from file";
    char buff[17];
    createFile(filename);
    writeToFile(filename,mass,17);
    readFromFile(filename, buff, 17);
    printf("%s",buff);
    
    exit(EXIT_SUCCESS);
}