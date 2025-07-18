#ifndef _UI_H_
#define _UI_H_

int UIInit();
int moveCurs();
int fillLine(int x, int startPosy, int line, int startPosRightx, char* str);
int fillFileAndFolder(struct dirent** files1, struct dirent** files2, char* path1, char* path2);
int changeDir(char** path, struct dirent** files, int selectLine);

#endif