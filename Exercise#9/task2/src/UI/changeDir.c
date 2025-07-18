#include <dirent.h>
#include <unistd.h>
#include "../getFile.h"
#include "../main.h"

int changeDir(char** path, struct dirent** files, int selectLine){
    int lenght=0;
    chdir((*files)[selectLine].d_name);
    getPath(path);
    getFileAndDir(files,&lenght,*path);
    return 0;
}