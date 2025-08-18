#ifndef _MSGBUF_H_
#define _MSGBUF_H_

#include <netinet/in.h>

struct msgbuf
{
    long mtype; /* тип сообщения, должен быть > 0 */
    int client_fd;
};

#endif