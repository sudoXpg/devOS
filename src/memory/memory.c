#include "memory.h"

void *memset(void *ptr, char c, size_t size){
    char *cptr = (char *) ptr;
    for(int i=0;i<size;i++){
        cptr[i]=c;
    }
    return ptr;
}