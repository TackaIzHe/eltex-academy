#ifndef _TREAD_ARG_STRUCT_
#define _TREAD_ARG_STRUCT_

struct thread_arg_struct{
    char name[30];
    int potreb;
    int ** stores;
    int ** busy;
};

#endif