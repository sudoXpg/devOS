#include "memory.h"

void *memset(void *ptr, char c, size_t size){
    char *cptr = (char *) ptr;
    for(int i=0;i<size;i++){
        cptr[i]=c;
    }
    return ptr;
}

int memcmp(void *src, void *dest, size_t size){
    char* src_ptr = (char*)src;
    char* dest_ptr = (char*)dest;
    for(int i=0;i<size;i++){
        if(src_ptr[i] != dest_ptr[i]){
            return src_ptr[i]<dest_ptr[i] ? -1 : 1;
        }
    }
    return 0;
}