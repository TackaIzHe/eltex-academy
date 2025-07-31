#ifndef _MAIN_H_
#define _MAIN_H_
#include "thread_arg_struct.h"

extern int WorkLoader;
void* buyer_func(void*);
void* loader_func(void*);
int log_func(struct thread_arg_struct* obj, int col, int shopNum);
int init_thread_obj(struct thread_arg_struct*** obj, int colBuyer, int colLoader, int** store, int** busy);

#endif