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

int paging_get_indexes(void *virtual_address, uint32_t *directory_index_out, uint32_t *table_index_out){    // finds which dir and page entries are used
    int ret=0;
    if(!paging_is_aligned(virtual_address)){        // checks if is a valid page address
        ret = ERROR_INVALID_ARG;
    }
    
    *directory_index_out = ((uint32_t)virtual_address/(PAGING_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE));
    *table_index_out = ((uint32_t) virtual_address % (PAGING_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE) / PAGING_PAGE_SIZE);
    return ret;
}

int paging_set(uint32_t *directory, void *virtaddr, uint32_t val){
    if(!paging_is_aligned(virtaddr)){
        return ERROR_INVALID_ARG;
    }
    uint32_t directory_index=0;
    uint32_t table_index=0;
    if(paging_get_indexes(virtaddr, &directory_index, &table_index)<0){
        return ERROR_INVALID_ARG;
    }
    uint32_t page_dir_entry = directory[directory_index];
    uint32_t *page_table = ((uint32_t*) (page_dir_entry & 0xfffff000));     //only get first 20 bits
    page_table[table_index] = val;
    return 0;
}