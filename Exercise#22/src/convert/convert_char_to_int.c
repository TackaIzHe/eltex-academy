#include <string.h>

int convert_char_to_int(char* string, int* res ){
    int len = strlen(string);
    int cur = 1;
    for(int i=0;i<len;i++){
        *res = *res + ((string[len-i-1] - 48) * cur);
        cur *= 10;
    }
}