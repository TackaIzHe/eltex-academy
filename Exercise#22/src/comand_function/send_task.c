#include <unistd.h>
#include <stdio.h>
#include "../driver_function/driver_func.h"

int send_task(pid_t pid, int timer){
    struct mess mess;
    mess.timer = timer;
    send_mess_to_driver(pid,mess);
}   