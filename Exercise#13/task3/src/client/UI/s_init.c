#include <ncurses.h>
#include "UI.h"

int s_init()
{
    initscr();
    keypad(stdscr, 1);
    curs_set(2);

    print_win();
    input_func();

    endwin();

    return 0;
}