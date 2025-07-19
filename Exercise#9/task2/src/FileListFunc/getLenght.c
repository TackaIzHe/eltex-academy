#include "FileListStruct.h"

int getLenght(struct FileList** start, int* lenght){
    *lenght = (*start)->end->lenght;
    return 0;
}