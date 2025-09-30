#include <malloc.h>
#include <string.h>
#include "list_struct.h"

int add(struct list_drivers *list, pid_t pid, int *lenght)
{
    int smeshenie = sizeof(struct list_drivers) * (*lenght + 1);
    struct list_drivers elem;
    *(struct list_drivers*)(list+smeshenie) = elem;
    ((struct list_drivers*)(list+smeshenie))->pid_driver = pid;
    strcpy(((struct list_drivers*)(list+smeshenie))->status, "Available");
    ((struct list_drivers*)(list+smeshenie))->next = 0;
    ((struct list_drivers*)(list+smeshenie))->lees = list->last;
    ((struct list_drivers*)(list+smeshenie))->last = ((struct list_drivers*)(list+smeshenie));
    if (*lenght == 0)
    {
        ((struct list_drivers*)(list+smeshenie))->lees = 0;
        list->next = ((struct list_drivers*)(list+smeshenie));
        list->lees = 0;
        list->last = ((struct list_drivers*)(list+smeshenie));
    }
    else
    {
        list->last->next = ((struct list_drivers*)(list+smeshenie));
        list->last = ((struct list_drivers*)(list+smeshenie));
    }
    *lenght = *lenght + 1;
    return 0;
}