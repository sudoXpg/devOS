#include "paging.h"

void paging_load_directory(uint32_t *directory);

uint32_t *current_directory = 0;        // pointer to current used directory table
// will give linear memory
struct paging_4gb *paging_new_4gb(uint8_t flags){
    uint32_t *directory = kzalloc(sizeof(uint32_t) * PAGING_ENTRIES_PER_TABLE);             // page directory
    int offset=0;
    for(int i=0;i<PAGING_ENTRIES_PER_TABLE;i++){                // need to create a page table for each directory entry, 1024 here
        uint32_t *page_table_entry = kzalloc(sizeof(uint32_t)* PAGING_ENTRIES_PER_TABLE);   // page table entry
        for(int j=0;j<PAGING_ENTRIES_PER_TABLE;j++){
            page_table_entry[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags;
        }
        offset += (PAGING_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE);            // after one page table next needs to start at the end of first
        directory[i] = (uint32_t) page_table_entry | flags | PAGING_IS_WRITEABLE ;     // writable page by default
    }

    struct paging_4gb *chunk_4gb = kzalloc(sizeof(struct paging_4gb));
    chunk_4gb->directory_entry = directory;
    return chunk_4gb;
}

void paging_switch(uint32_t *directory){
    paging_load_directory(directory);
    current_directory = directory;
}

int paging_is_aligned(void *address){
    return ((uint32_t) address % PAGING_PAGE_SIZE) ==0;
}
