#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <malloc.h>

int main(){
    int* disc;
    disc = malloc(sizeof(int)*2); 
    pipe(disc);
    pid_t child;
    int status;
    write(disc[1],"hi!",4);
    close(disc[1]);
    child = fork();
    if(child == 0){
        char* str;
        str = malloc(sizeof(char)*4);
        read(disc[0],str,4);
        printf("%s\n",str);
        free(str);
        close(disc[0]);
        exit(EXIT_SUCCESS);
    }else{
        wait(&status);
    }
    free(disc);
    exit(EXIT_SUCCESS);
}