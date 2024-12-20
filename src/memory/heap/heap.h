#ifndef HEAP_H
#define HEAP_H

#include"../../headers/constants.h"
#include<stdint.h>
#include<stddef.h>
#include"../../display/display.h"
#include"../memory.h"

#define HEAP_TABLE_ENTRY_TAKEN              0x01
#define HEAP_TABLE_ENTRY_FREE               0x00
#define HEAP_TABLE_ENTRY_HAS_NEXT           0b10000000
#define HEAP_TABLE_ENTRY_IS_FIRST           0b01000000                   


typedef unsigned char HEAP_TABLE_ENTRY;


struct heap_table{
    HEAP_TABLE_ENTRY *table_entries;
    size_t size;
};

struct heap{
    struct heap_table *table;
    void *start_addr;
};

int create_heap(struct heap* heap, void *start_ptr, void *end_ptr, struct heap_table *table);
void *heap_malloc(struct heap *heap, size_t size);
void heap_free(struct heap *heap, void *ptr);


#endif