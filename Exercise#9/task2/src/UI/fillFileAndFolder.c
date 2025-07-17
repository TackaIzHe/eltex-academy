#include <dirent.h>
#include <ncurses.h>
#include <malloc.h>
#include "../getFile.h"

int fillFileAndFolder(struct dirent** files1, struct dirent** files2, char* path1, char* path2){
    int length1 = 0;
    int length2 = 0;
    int folder = 4;
    int file = 8;
    int y = 0, x = 0;
    getmaxyx(stdscr,y,x);
    int startPosLeftx = 1;
    int startPosy = 3;
    int startPosRightx = x/2+2;
    getFileAndDir(files1,&length1,path1);
    for(int i=0;i<length1;i++){
        mvprintw(startPosy+i,startPosLeftx,(*files1+i)->d_name);
    }
    return 0;
}