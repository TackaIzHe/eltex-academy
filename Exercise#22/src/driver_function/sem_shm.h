#ifndef _SEM_SHM_H_
#define _SEM_SHM_H_

#include <semaphore.h>

#define SHM_PATH "/shm_file"
#define SEM_PATH "/sem_file"
#define SHM_LENGHT 3096

extern void* addr_shm;
extern sem_t* sem;
#endif