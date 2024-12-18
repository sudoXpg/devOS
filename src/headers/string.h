#ifndef STRING_H
#define STRING_H
#include<stdint.h>
#include<stddef.h>

size_t strlen(const char *string){
    size_t length=0;
    while(string[length]){
        length++;
    }
    return length;
}

#endif