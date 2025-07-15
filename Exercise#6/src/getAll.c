#include "stract.h"
#include "main.h"
#include <stdio.h>

int getAll(struct abonent **startObj, struct abonent **endObj, int length)
{
    printf("Весь справочник: %d\n", length);
    int isWork = 1;
    struct abonent *next = *startObj;
    while (isWork)
    {
        if (next != 0)
        {
            get(*next);
            if (next == *endObj)
            {
                isWork = 0;
                return 0;
            }
            next = next->next;
        }
        else
        {
            printf("Справочник пуст\n");
            isWork = 0;
            break;
        }
    }

    return 0;
}