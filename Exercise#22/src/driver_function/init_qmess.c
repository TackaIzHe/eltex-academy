#include <mqueue.h>
#include "mess_struct.h"

int init_qmess(){
    mqd_t mq_res;
    mqd_t mq_req;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 2;
    attr.mq_msgsize = sizeof(struct mess);
}