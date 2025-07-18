#include <dirent.h>
#include <ncurses.h>
#include <malloc.h>
#include "../getFile.h"
#include "UI.h"

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
    getFileAndDir(files2,&length2,path2);
    // attron(COLOR_PAIR(1));
    // for (int i = 0;i<y-5;i++){
    //     fillLine(x, startPosy, i, startPosLeftx, " ");
    //     fillLine(x, startPosy, i, startPosRightx, " ");
    // }
    
    attron(COLOR_PAIR(2));
    
    for(int i=0;i<length1;i++){
        mvprintw(startPosy+i,startPosLeftx,(*files1+i)->d_name);
        mvprintw(startPosy+i,startPosRightx,(*files2+i)->d_name);
    }
    for(int i=0;i<length1;i++){
        mvprintw(startPosy+i,x/2-7,(*files1+i)->d_type==4?"Folder":"File");
        mvprintw(startPosy+i,x-7,(*files2+i)->d_type==4?"Folder":"File");
    }
    length1 = 0;
    length2 = 0;
    return 0;
}