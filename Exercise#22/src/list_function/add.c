#include <malloc.h>
#include <string.h>
#include "list_struct.h"

int add(struct list_drivers *list, pid_t pid, int *lenght)
{
    struct list_drivers *elem;

    elem = malloc(sizeof(struct list_drivers));

    elem->pid_driver = pid;
    strcpy(elem->status, "Available");
    elem->next = 0;
    elem->lees = list->last;
    elem->last = elem;

    if (*lenght == 0)
    {
        elem->lees = 0;
        list->next = elem;
        list->lees = 0;
        list->last = elem;
    }
    else
    {
        list->last->next = elem;
        list->last = elem;
    }
    *lenght = *lenght + 1;
    return 0;
}