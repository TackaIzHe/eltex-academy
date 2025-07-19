#include "../FileListFunc/FileListStruct.h"
#include <unistd.h>
#include "../getFile.h"
#include "../main.h"

int changeDir(char **path, struct FileList **files, int selectLine)
{
    chdir(*path);
    chdir(getItem(files, selectLine + 1)->name);
    getPath(path);
    getFileAndDir(files, *path);
    return 0;
}