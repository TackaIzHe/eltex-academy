#include "stract.h"
#include "main.h"
#include <stdio.h>
#include <malloc.h>

int freeList(struct abonent **startObj, struct abonent **endObj)
{
    int isWork = 1;
    struct abonent *next = *startObj;
    while (isWork)
    {
        free(next);
        if (next == *endObj)
        {
            isWork = 0;
            return 0;
        }
        next = next->next;
    }
    return 0;
}