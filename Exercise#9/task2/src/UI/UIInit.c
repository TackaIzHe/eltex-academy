#include <dirent.h>
#include <ncurses.h>

int UIInit(){
    int y = 0, x = 0;
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLUE);
    attron(COLOR_PAIR(1));
    getmaxyx(stdscr,y,x);
    for(int i = 0;i<y;i++){
        for(int j = 0; j<x;j++){
            mvaddch(i,j,' ');
        }
    }
    for(int i = 0;i<x;i++){
        mvaddch(0,i,'-');
        mvaddch(2,i,'-');
        mvaddch(y-1,i,'-');
        
        mvaddch(i,0,'|');
        mvaddch(i,x-1,'|');
        
        mvaddch(i,x/2-1,'|');
        mvaddch(i,x/2-8,'|');
        mvaddch(i,x/2+1,'|');
        mvaddch(i,x-8,'|');
    }

    attron(COLOR_PAIR(2));
    mvprintw(1,1,"Filename");
    mvprintw(1,x/2-8,"| Type ");
    mvprintw(1,x/2+2,"Filename");
    mvprintw(1,x-8,"| Type ");
    return 0;
}