#ifndef _DRIVER_FUNC_H_
#define _DRIVER_FUNC_H_

int get_mess_from_drivers();
int init_driver(struct list_drivers* list, int* lenght);
int send_mess_to_driver();

#endif