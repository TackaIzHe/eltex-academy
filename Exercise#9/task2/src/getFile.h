#ifndef _GET_FILE_H
#define _GET_FILE_H

int getFileAndDir(struct dirent** files, int* length, char* path);
int getPath(char** path);
#endif