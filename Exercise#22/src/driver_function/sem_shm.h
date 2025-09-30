#ifndef _SEM_SHM_H_
#define _SEM_SHM_H_

#include <semaphore.h>
#include "../list_function/list_struct.h"

#define SHM_PATH "/shm_file"
#define SHM_LENGHT 3096

int init_mman(struct list_drivers list, void** addr_shm);
int reopen_shm(void** addr_shm);
int close_mman(void* addr_shm);

#endif