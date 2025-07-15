#include "stract.h"
#include "main.h"
#include <stdio.h>

int search(struct abonent **startObj, struct abonent **endObj, int length)
{
    char name[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int isWork = 1;
    struct abonent *next = *startObj;
    printf("Введите имя: \n");
    scanf("%10s", name);
    printf("\nНайденые записи: \n");

    while (isWork)
    {
        if (next == 0)
        {
            isWork = 0;
            return 0;
        }
        for (int j = 0; j < 10; j++)
        {
            if (next->name[j] == 0 && name[j] == 0)
            {
                get(*next);
                break;
            }
            else if (next->name[j] == name[j])
            {
                continue;
            }
            break;
        }
        next = next->next;
    }
    return 0;
}