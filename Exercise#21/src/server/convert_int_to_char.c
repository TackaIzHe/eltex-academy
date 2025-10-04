#include <string.h>

int convert_int_to_char(int num, char* str, int lenght){
    memset(str,0,lenght);
    int count = 0;
    int n = num;
    while(n>0){
        n/=10;
        count++;
    }
    for(int i=count-1; i>=0;i--){
        str[i] = (num%10) + 48;
        num/=10;   
    }
    strcat(str,"");
}