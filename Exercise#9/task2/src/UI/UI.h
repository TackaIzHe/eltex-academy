#ifndef _UI_H_
#define _UI_H_

#include "../FileListFunc/FileListStruct.h"

int UIInit();
int moveCurs();
int fillLine(int x, int startPosy, int line, int startPosRightx, char* str);
int fillFileAndFolder(struct FileList** files1, struct FileList** files2, char* path1, char* path2);
int changeDir(char** path, struct FileList** files, int selectLine);

#endif