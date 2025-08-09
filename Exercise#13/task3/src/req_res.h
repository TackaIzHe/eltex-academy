#ifndef _REQ_RES_H_
#define _REQ_RES_H_

#include <mqueue.h>

struct req_res{
    mqd_t req;
    mqd_t res;
};

#endif