#include <mqueue.h>
#include <string.h>

int send_func(char* mess, mqd_t req){
    mq_send(req,mess,strlen(mess)+1,0);
    return 0;
}