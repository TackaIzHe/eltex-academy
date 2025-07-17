#include <ncurses.h>

int fillLine(int x, int startPosy, int line, int startPosRightx, char* str)
{
    for (int i = 0; i < x / 2 - 9; i++)
    {
        mvprintw(startPosy + line, startPosRightx + i, str);
    }
    return 0;
}