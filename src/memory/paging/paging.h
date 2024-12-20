#ifndef PAGING_H
#define PAGING_H

#include<stdint.h>
#include<stddef.h>
#include "memory/heap/kheap.h"

#define PAGING_CACHE_DISABLED           0b00010000
#define PAGING_WRITE_THROUGH            0b00001000
#define PAGING_ACCESS_FROM_ALL          0b00000100
#define PAGING_IS_WRITEABLE             0b00000010
#define PAGING_IS_PRESENT               0b00000001

#define PAGING_ENTRIES_PER_TABLE        1024
#define PAGING_PAGE_SIZE                4096

struct paging_4gb{
    uint32_t *directory_entry;          // pointer to the page directory!
};

void paging_switch(uint32_t *directory);
struct paging_4gb *paging_new_4gb(uint8_t flags);
void enable_paging();
int paging_set(uint32_t *directory, void *virtaddr, uint32_t val);
int paging_is_aligned(void *address);

#endif