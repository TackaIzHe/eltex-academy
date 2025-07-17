#include <dirent.h>
#include <ncurses.h>
#include "UI.h"

int mcInit(){
    initscr();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    UIInit();
    moveCurs();
    echo();
    curs_set(2);
    endwin();
    return 0;
}