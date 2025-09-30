#include <string.h>
#include <unistd.h>
#include "../driver_function/driver_func.h"

int send_comand(pid_t pid, char* comand){
    struct mess mess;
    strcpy(mess.status, comand);
    send_mess_to_driver(pid,mess);
}