#include <dirent.h>
#include <malloc.h>
#include <stdlib.h>
#include <ncurses.h>

int getFileAndDir(struct dirent **files, int *length, char *path)
{
    DIR *dir;
    struct dirent *d;
    dir = opendir(path);
    if (dir)
    {
        while ((d = readdir(dir)) != 0)
        {
            *length = *length + 1;
            *files = (struct dirent *)realloc(*files, sizeof(struct dirent) * *length);
            if (*files < 0)
            {
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < sizeof(d->d_name); i++)
            {
                (*files + *length - 1)->d_name[i] = d->d_name[i];
                if (d->d_name[i] == '\0')
                {
                    break;
                }
            }
            (*files + *length - 1)->d_type = d->d_type;
        }
        closedir(dir);
    }
    else
    {
        return -1;
    }
    return 0;
}