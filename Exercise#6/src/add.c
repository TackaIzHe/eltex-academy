#include "stract.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include "main.h"

static int id = 0;

int add(struct abonent **startObj, struct abonent **endObj, int *length)
{
    if (*length == 100)
    {
        printf("В справочнике нет места\n");
        return 0;
    }
    *length = *length + 1;
    struct abonent *newObj;
    size_t size = sizeof(struct abonent);
    newObj = (struct abonent *)malloc(size);
    if (newObj < 0)
    {
        perror("Out of memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++)
    {
        newObj[0].name[i] = 0;
        newObj[0].second_name[i] = 0;
        newObj[0].tel[i] = 0;
    }
    newObj[0].id = ++id;
    printf("Введите имя\n");
    scanf("%10s", newObj[0].name);
    printf("Введите фамилию\n");
    scanf("%10s", newObj[0].second_name);
    printf("Введите телефон\n");
    scanf("%10s", newObj[0].tel);
    if (*length <= 1)
    {
        *startObj = newObj;
        *endObj = newObj;
        return 0;
    }
    get(**startObj);
    (*endObj)->next = newObj;
    newObj[0].prev = *endObj;
    *endObj = newObj;
    return 0;
}