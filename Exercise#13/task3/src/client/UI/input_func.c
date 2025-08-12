#include <ncurses.h>
#include <string.h>
#include "UI.h"
#include "client.h"
#include "../res_struct.h"
#include <fcntl.h>
#include <stdlib.h>
#include <mqueue.h>
#include <pthread.h>

int input_func()
{
    mqd_t mq;
    mqd_t req;
    mqd_t res;
    pthread_t get_mess_thread;
    struct pthread_arg arg;
    char queue_name[256];
    int y, x = 0;
    int cur_pos = 1;
    int cur_x_pos = 1;
    getmaxyx(stdscr, y, x);
    int is_con = 0;

    char buff[256];
    char ch[2];
    strcpy(buff, "");

    strcpy(buff, "");
    while (1)
    {
        strcpy(ch, "");
        int input = getch();
        if (input == KEY_BACKSPACE)
        {
            int buffLen = strlen(buff);
            if (buffLen == 0 || cur_x_pos <= 1)
            {
                mvprintw(y - 2, 1, "");
                continue;
            }
            else
            {
                buff[buffLen - 1] = '\0';
                for (int i = 1; i < x - 1; i++)
                {
                    mvprintw(y - 2, i, " ");
                }
                mvprintw(y - 2, 1, buff);
                cur_x_pos--;
            }
            continue;
        }
        if (input == '\n')
        {
            for (int i = 1; i < x - 1; i++)
            {
                mvprintw(y - 2, i, " ");
            }
            if (cur_pos == y - 3)
            {
                cur_pos = 1;
            }
            if (is_con == 0)
            {
                mq = mq_open("/mq_message", O_RDWR);
                if (mq == (mqd_t)-1)
                {
                    perror("Ошибка подключения к очереди\n");
                    exit(EXIT_FAILURE);
                }

                mq_send(mq, buff, strlen(buff) + 1, 0);
                mq_receive(mq, buff, 256, 0);
                
                strcpy(queue_name, buff);

                mq_close(mq);

                connect_func(queue_name, &req, &res);
                arg.res = res;
                pthread_create(&get_mess_thread,NULL,get_mess_func,&arg);
                is_con++;
            }
            else
            {
                send_func(buff, req);
            }
            strcpy(buff, "");
            mvprintw(y - 2, 1, "");
        }
        ch[0] = input;
        if(input != '\n')
        strcat(buff, ch);
        cur_x_pos++;
    }
    mq_close(req);
    mq_close(res);
}