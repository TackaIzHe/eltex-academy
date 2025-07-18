#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>
int getPath(char** path){
    getcwd(*path,PATH_MAX);
    return 0;
}