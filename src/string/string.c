#include "string.h"

size_t strlen(const char *string){
    size_t length=0;
    while(string[length]){
        length++;
    }
    return length;
}

int isdigit(char c){
    if(c>=48 && c<=57){         // from ascii table
        return 1;
    }
    return 0;
}


int todigit(char c){
    return c - 48;              // from ascii table
}