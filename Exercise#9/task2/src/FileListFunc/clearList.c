#include <malloc.h>
#include "FileListStruct.h"

int clearList(struct FileList** start){
    struct FileList* next = *start;
    if(*start == 0){
        return 0;
    }
    while(1){
        if(next == 0){
            *start = 0;
            break;
        }
        free(next);
        next = next->next;
    }
    return 0;
}