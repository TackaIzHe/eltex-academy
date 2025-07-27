#include <stdio.h>

int proc(char* name,int pid, int ppid){
    printf("%s pid: %d\n",name,pid);
    printf("%s ppid: %d\n",name,ppid);
    return 0;
}