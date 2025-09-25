#ifndef _LIST_STRUCT_H_
#define _LIST_STRUCT_H_

#include <unistd.h>

struct list_drivers{
    pid_t pid_driver;
    char status[10];
    struct list_drivers* next;
    struct list_drivers* lees;
    struct list_drivers* last;

};


#endif