#ifndef MEMORY_H
#define MEMORY_H

#include<stdint.h>
#include<stddef.h>

void *memset(void *ptr, char c, size_t size);
int memcmp(void *src, void *dest, size_t size);

#endif