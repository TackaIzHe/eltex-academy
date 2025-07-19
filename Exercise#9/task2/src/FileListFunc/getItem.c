#include "FileListStruct.h"

struct FileList* getItem(struct FileList** start, int id){
    struct FileList* next = *start;
    while(1){
        if(next == 0){
            return 0;
        }
        if(next->lenght == id){
            return next;
        }
        next = next->next;
    }
    return 0;
}