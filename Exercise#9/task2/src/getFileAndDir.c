#include <dirent.h>
#include <malloc.h>
#include <stdlib.h>
#include "FileListFunc/FileListStruct.h"

int getFileAndDir(struct FileList** start, char *path)
{
    DIR *dir;
    struct dirent *d;
    dir = opendir(path);
    clearList(start);
    if (dir)
    {
        while ((d = readdir(dir)) != 0)
        {
            struct FileList* new;
            new = (struct FileList *)malloc(sizeof(struct FileList));
            if (new < 0)
            {
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < sizeof(d->d_name); i++)
            {
                new->name[i] = d->d_name[i];
                if (d->d_name[i] == '\0')
                {
                    break;
                }
            }
            new->type = d->d_type;
            push(start,&new);
        }
        closedir(dir);
    }
    else
    {
        return -1;
    }
    return 0;
}