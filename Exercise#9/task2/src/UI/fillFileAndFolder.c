#include "../FileListFunc/FileListStruct.h"
#include <ncurses.h>
#include <malloc.h>
#include "../getFile.h"
#include "UI.h"

int fillFileAndFolder(struct FileList** files1, struct FileList** files2, char* path1, char* path2){
    int length1 = 0;
    int length2 = 0;
    int folder = 4;
    int file = 8;
    int y = 0, x = 0;
    getmaxyx(stdscr,y,x);
    int startPosLeftx = 1;
    int startPosy = 3;
    int startPosRightx = x/2+2;
    attron(COLOR_PAIR(1));
    for (int i = 0;i<y-5;i++){
        fillLine(x, startPosy, i, startPosLeftx, " ");
        fillLine(x, startPosy, i, startPosRightx, " ");
    }
    for(int i=0;i<y-5;i++){
        mvprintw(startPosy+i,x/2-7,"      ");
        mvprintw(startPosy+i,x-7,"      ");
    }
    attron(COLOR_PAIR(2));
    struct FileList* next1 = *files1;
    struct FileList* next2 = *files2;
    while(1){
        if(next1 == 0){
            break;
        }
        mvprintw(startPosy+next1->lenght-1,startPosLeftx,next1->name);
        next1 = next1->next;
    }
    while(1){
        if(next2 == 0){
            break;
        }
        mvprintw(startPosy+next2->lenght-1,startPosRightx,next2->name);
        next2 = next2->next;
    }
    next1 = *files1;
    next2 = *files2;
    while(1){
        if(next1 == 0){
            break;
        }
        mvprintw(startPosy+next1->lenght-1,x/2-7,next1->type==4?"Folder":"File");
        next1 = next1->next;
    }
    while(1){
        if(next2 == 0){
            break;
        }
        mvprintw(startPosy+next2->lenght-1,x-7,next2->type==4?"Folder":"File");
        next2 = next2->next;
    }
    return 0;
}