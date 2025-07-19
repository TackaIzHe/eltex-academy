#include "FileListStruct.h"

int push(struct FileList **start, struct FileList **cur)
{
    if (*start == 0)
    {
        *start = *cur;
        (*start)->lenght = 1;
        (*start)->end = *start;
        (*start)->next = 0;
        (*start)->prev = 0;
        return 0;
    }
        (*start)->end->next = *cur;
        (*start)->end->next->prev = (*start)->end;
        (*start)->end->next->lenght = (*start)->end->lenght + 1;
        (*start)->end = (*start)->end->next;
        (*start)->end->next = 0;
    return 0;
}