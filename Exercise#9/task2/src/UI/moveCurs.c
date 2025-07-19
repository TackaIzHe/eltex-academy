#include <ncurses.h>
#include <malloc.h>
#include <linux/limits.h>
#include "UI.h"
#include "../getFile.h"
#include "../FileListFunc/FileListStruct.h"

int moveUp(int *line, int x, int startPosy, int startPosLeftx)
{
    *line = *line - 1;
    attron(COLOR_PAIR(1));
    fillLine(x, startPosy, *line + 1, startPosLeftx, " ");
    attron(COLOR_PAIR(2));
    fillLine(x, startPosy, *line, startPosLeftx, " ");
}
int moveDown(int *line, int x, int startPosy, int startPosLeftx)
{
    *line = *line + 1;
    attron(COLOR_PAIR(1));
    fillLine(x, startPosy, *line - 1, startPosLeftx, " ");
    attron(COLOR_PAIR(2));
    fillLine(x, startPosy, *line, startPosLeftx, " ");
}

int moveCurs()
{
    struct FileList* files1;
    struct FileList* files2;
    files1 = 0;
    files2 = 0;
    char *path1;
    char *path2;
    path1 = malloc(PATH_MAX);
    path2 = malloc(PATH_MAX);
    getPath(&path1);
    getPath(&path2);
    int y = 0, x = 0;
    getmaxyx(stdscr, y, x);
    int startPosLeftx = 1;
    int startPosy = 3;
    int startPosRightx = x / 2 + 2;
    int input = 0;
    int pos = 1;
    int leftLine = 0;
    int rightLine = 0;
    attron(COLOR_PAIR(2));
    fillLine(x, startPosy, leftLine, startPosLeftx, " ");
    getFileAndDir(&files1,path1);
    getFileAndDir(&files2,path2);
    do
    {
        fillFileAndFolder(&files1, &files2, path1, path2);
        if (pos == 0)
        {
            fillLine(x, startPosy, rightLine, startPosRightx, " ");
            mvprintw(startPosy+rightLine, startPosRightx, getItem(&files2,rightLine+1)->name);
        }
        else
        {
            fillLine(x, startPosy, leftLine, startPosLeftx, " ");
            mvprintw(startPosy+leftLine, startPosLeftx, getItem(&files1,leftLine+1)->name);
        }
        input = getch();
        if (input == '\t')
        {
            if (pos == 0)
            {
                attron(COLOR_PAIR(1));
                fillLine(x, startPosy, rightLine, startPosRightx, " ");
                attron(COLOR_PAIR(2));
                fillLine(x, startPosy, leftLine, startPosLeftx, " ");
                pos = 1;
            }
            else
            {
                attron(COLOR_PAIR(1));
                fillLine(x, startPosy, leftLine, startPosLeftx, " ");

                attron(COLOR_PAIR(2));
                fillLine(x, startPosy, rightLine, startPosRightx, " ");
                pos = 0;
            }
        }
        else if (input == '\n')
        {
            if (pos == 1)
            {
                changeDir(&path1, &files1, leftLine);
                for (int i = leftLine; i > 0; i--)
                {
                    moveUp(&leftLine, x, startPosy, startPosLeftx);
                }
            }
            else
            {
                changeDir(&path2, &files2, rightLine);
                for (int i = rightLine; i > 0; i--)
                {
                    moveUp(&rightLine, x, startPosy, startPosRightx);
                }
            }
        }
        else if (input == KEY_UP)
        {
            if (pos == 1)
            {
                if (leftLine > 0 && getItem(&files1, leftLine)->name != 0)
                {
                    moveUp(&leftLine, x, startPosy, startPosLeftx);
                }
            }
            else
            {
                if (rightLine > 0 && getItem(&files2, rightLine)->name != 0)
                {
                    moveUp(&rightLine, x, startPosy, startPosRightx);
                }
            }
        }
        else if (input == KEY_DOWN)
        {
            if (pos == 1)
            {
                int i=0;
                getLenght(&files1,&i);
                if (leftLine < y - 5 && i > leftLine+1)
                {
                    moveDown(&leftLine, x, startPosy, startPosLeftx);
                }
            }
            else
            {
                int i = 0;
                getLenght(&files2,&i);
                if (rightLine < y - 5 && i>rightLine+1)
                {
                    moveDown(&rightLine, x, startPosy, startPosRightx);
                }
            }
        }
    } while (input != 27);
    free(path1);
    free(path2);
    return 0;
}