#include <ncurses.h>

int print_win(){
    int x, y = 0;
    getmaxyx(stdscr, y, x);

    for (int i = 0; i < x; i++)
    {
        mvaddch(i, x - 1, '|');
        mvaddch(i, 0, '|');

        mvaddch(i, x - 30, '|');

        mvaddch(0, i, '=');
        mvaddch(y - 1, i, '=');
        mvaddch(y - 3, i, '=');
    }

    for (int i = 1; i < x - 1; i++)
    {
        mvprintw(y - 2, i, " ");
    }
    mvprintw(y - 2, 1, "");

    return 0;
}