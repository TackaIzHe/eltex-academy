#ifndef _DRIVER_FUNC_H_
#define _DRIVER_FUNC_H_

#include "mess_struct.h"

int init_driver(void** addr_shm);
int send_mess_to_driver(int pid, struct mess mess);

#endif