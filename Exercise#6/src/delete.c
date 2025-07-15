#include <stdio.h>
#include "stract.h"
#include <malloc.h>

int delet(struct abonent **startObj, struct abonent **endObj, int *length)
{
    if (*length == 0)
    {
        printf("В справочнике нет записей\n");
        return 0;
    }
    int id = 0;
    int isWork = 1;
    struct abonent *next = *startObj;
    printf("Введите номер записи\n");
    scanf("%d", &id);
    while (isWork)
    {
        if (next == 0)
        {
            printf("Запись не найдена\n");
            isWork = 0;
            break;
        }
        else if (next->id == id)
        {
            if (*startObj == *endObj)
            {
                *startObj = 0;
                *endObj = 0;
            }
            else
            {
                if (next->prev != 0)
                {
                    next->prev->next = next->next;
                }
                else
                {
                    *startObj = next->next;
                }
                if (next->next != 0)
                {
                    next->next->prev = next->prev;
                }
                else
                {
                    *endObj = next->prev;
                }
            }
            free(next);
            isWork = 0;
            *length = *length - 1;
            break;
        }
        next = next->next;
    }
    return 0;
}