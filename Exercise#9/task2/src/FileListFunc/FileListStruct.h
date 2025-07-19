#ifndef _FILE_LIST_STRUCT_H_
#define _FILE_LIST_STRUCT_H_

struct FileList{
    char name[256];
    int type;
    int lenght;
    struct FileList* next;
    struct FileList* prev;
    struct FileList* end;

};

int push(struct FileList** start, struct FileList** cur);
int pop(struct FileList** start, struct FileList** end, struct FileList** cur);
int clearList(struct FileList** start);
int getLenght(struct FileList** start, int* lenght);
struct FileList* getItem(struct FileList** start, int id);
#endif