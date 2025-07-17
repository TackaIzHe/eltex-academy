#include <dirent.h>
#include <ncurses.h>
#include <malloc.h>
#include "UI.h"

int moveCurs(){
    struct dirent* files1; 
    struct dirent* files2;
    files1 = malloc(sizeof(struct dirent));
    files2 = malloc(sizeof(struct dirent));
    char* path1;
    char* path2;
    path1 = malloc(2);
    path2 = malloc(2);
    path1[0] = '.';
    path1[1] = '\0';
    path2[0] = '.';
    path2[1] = '\0';
    int y = 0, x = 0;
    getmaxyx(stdscr,y,x);
    int startPosLeftx = 1;
    int startPosy = 3;
    int startPosRightx = x/2+2;
    int input = 0;
    int pos = 1;
    int leftLine = 0;
    int rightLine = 0;
    attron(COLOR_PAIR(2));
    fillLine(x,startPosy, leftLine, startPosLeftx," ");
    
    do{
        fillFileAndFolder(&files1,&files2,path1,path2);
        input = getch();
        if(input == '\t'){
            if(pos == 0){
                attron(COLOR_PAIR(1));
                fillLine(x,startPosy, rightLine, startPosRightx, " ");
                attron(COLOR_PAIR(2));
                fillLine(x,startPosy, leftLine, startPosLeftx, " ");
                pos = 1;
            }else{
                attron(COLOR_PAIR(1));
                fillLine(x,startPosy, leftLine, startPosLeftx, " ");
                    
                attron(COLOR_PAIR(2));
                fillLine(x,startPosy, rightLine, startPosRightx, " ");
                pos = 0;
            }
        }
        else if(input == KEY_UP){
            if(pos == 1){
                if(leftLine >0){
                    leftLine--;
                    attron(COLOR_PAIR(1));
                    fillLine(x,startPosy, leftLine+1, startPosLeftx, " ");
                    attron(COLOR_PAIR(2));
                    fillLine(x,startPosy, leftLine, startPosLeftx, " ");
                }
            }else{
                if(rightLine >0){
                    rightLine--;
                    attron(COLOR_PAIR(1));
                    fillLine(x,startPosy, rightLine+1, startPosRightx, " ");
                    attron(COLOR_PAIR(2));
                    fillLine(x,startPosy, rightLine, startPosRightx, " ");
                }
            }
        }
        else if(input == KEY_DOWN){
            if(pos == 1){
                if(leftLine <y-5){
                    leftLine++;
                    attron(COLOR_PAIR(1));
                    fillLine(x,startPosy, leftLine-1, startPosLeftx, " ");
                    attron(COLOR_PAIR(2));
                    fillLine(x,startPosy, leftLine, startPosLeftx, " ");
                }
            }else{
                if(rightLine <y-5){
                    rightLine++;
                    attron(COLOR_PAIR(1));
                    fillLine(x,startPosy, rightLine-1, startPosRightx, " ");
                    attron(COLOR_PAIR(2));
                    fillLine(x,startPosy, rightLine, startPosRightx, " ");
                }
            }
        }
    }
    while(input != 27);
    free(files1);
    free(files2);
    free(path1);
    free(path2);
    return 0;
}