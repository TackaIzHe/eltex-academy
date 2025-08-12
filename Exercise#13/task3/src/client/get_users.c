#include <mqueue.h>
#include <ncurses.h>
#include <string.h>

int get_users(mqd_t req, int* cur_pos_user){
    char buff[256];
    int x = 0;
    x = getmaxx(stdscr);
    while(1){
        mq_receive(req,buff,256,0); 
        if(strcmp(buff,";;users-list-end;;") == 0 || strcmp(buff,";;user-connect-end;;") == 0){
            break;
        }
        *cur_pos_user = *cur_pos_user + 1;
        mvprintw(*cur_pos_user,x-29,buff);
    }
}