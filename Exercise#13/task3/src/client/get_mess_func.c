#include <ncurses.h>
#include <mqueue.h>
#include <string.h>
#include "UI/UI.h"
#include "res_struct.h"
#include "UI/client.h"

void* get_mess_func(void* arg){
    struct pthread_arg* a = (struct pthread_arg*)arg;
    int x, y = 0;
    getmaxyx(stdscr, y, x);
    int cur_pos = 1;
    int cur_pos_user = 0;
    char buff[256];
    strcpy(buff,"");
    while(1){
        mq_receive(a->res,buff,256,0);
        if(cur_pos == y-2){
            cur_pos = 1;
        }

        if(strcmp(buff,";;users-list;;") == 0){ // ;;users-list-end;;
            get_users(a->res,&cur_pos_user);
            mvprintw(y-2,1,"");
            continue;
        }
        if(strcmp(buff,";;user-connect;;") == 0){ // ;;user-connect-end;;
            get_users(a->res,&cur_pos_user);
            mvprintw(y-2,1,"");
            continue;
        }

        for (size_t i = 0; i < x-30; i++)
        {
            mvprintw(cur_pos,i," ");    
        }
        
        mvprintw(cur_pos,1,buff);
        strcpy(buff,"");
        print_win();
        mvprintw(y-2,1,"");
        cur_pos++;
    }
}