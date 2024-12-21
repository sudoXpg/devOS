#ifndef PARSE_PATH
#define PARSE_PATH

#include "../headers/constants.h"
#include "../string/string.h"
#include "../memory/memory.h"
#include "../memory/heap/kheap.h"

struct root{
    int drive_num;
    struct path *first;
};

struct path{
    const char *first;
    struct path *next;
};

#endif