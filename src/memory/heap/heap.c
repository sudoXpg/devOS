#include "heap.h"

int heap_align_check(void *ptr){
    return ((unsigned int)ptr % HEAP_BLOACK_SIZE)==0;
}

int heap_table_check(void *start_ptr, void *end_ptr, struct heap_table *table){
    size_t table_size = (size_t)(end_ptr-start_ptr);
    size_t total_blocks = table_size/HEAP_BLOACK_SIZE;
    if(table->size!=total_blocks){
        return ERROR_MEMORY;
    }
    return 0;
}

int create_heap(struct heap* heap, void *start_ptr, void *end_ptr, struct heap_table *table){
    int ret=0;
    
    if(!heap_align_check(start_ptr) || !heap_align_check(end_ptr)){
        return ERROR_INVALID_ARG;
    }
    
    memset(heap,0,sizeof(struct heap));
    heap->start_addr=start_ptr;
    heap->table=table;
    
    if((ret = heap_table_check(start_ptr,end_ptr, table))<0){
        return ret;
    }
    
    size_t table_size = sizeof(HEAP_TABLE_ENTRY) * table->size;
    memset(table->table_entries,HEAP_TABLE_ENTRY_FREE,table_size);      // initialising the heap


    return ret;
}

uint32_t heap_align_value(uint32_t value){
    if(value % HEAP_BLOACK_SIZE ==0){
        return value;
    }
    value = (value - ( value % HEAP_BLOACK_SIZE));
    value += HEAP_BLOACK_SIZE;
    return value;
}

int heap_get_start_block(struct heap *heap,uint32_t total_blocks){
    struct heap_table *table = heap->table;
    size_t current_block = 0;
    size_t start_block = -1;
    for(size_t i=0;i<=table->size;i++){
        if( (table->table_entries[i] & 0xf) != HEAP_TABLE_ENTRY_FREE){
            current_block=0;
            start_block=-1;
            continue;
        }
        if(start_block==-1){        // is the start block
            start_block=i;
        }
        current_block++;
        if(current_block==total_blocks){
            break;
        }
    }
    if(start_block==-1){
        return ERROR_NO_MEMORY;
    }
    return start_block;
}

void *heap_block_to_address(struct heap *heap, uint32_t start_block){
    return heap->start_addr +(start_block*HEAP_BLOACK_SIZE);        // start +offset {offset = start*blocksize}
}

void mark_heap_blocks_as_taken(struct heap *heap, uint32_t start_block,uint32_t total_blocks){
    uint32_t end_block = (start_block + total_blocks)-1;          // starts at index 0
    HEAP_TABLE_ENTRY entry = HEAP_TABLE_ENTRY_TAKEN | HEAP_TABLE_ENTRY_IS_FIRST;    
    if(total_blocks>1){
        entry |= HEAP_TABLE_ENTRY_HAS_NEXT;
    }
    for(int i=start_block;i<=end_block;i++){
        heap->table->table_entries[i] = entry;
        entry=HEAP_TABLE_ENTRY_TAKEN;
        if(i!=end_block-1){
            entry|=HEAP_TABLE_ENTRY_HAS_NEXT;
        }
    }
}

void *heap_allocate_blocks(struct heap *heap, uint32_t total_blocks){
    void *address=0;
    uint32_t start_block = heap_get_start_block(heap,total_blocks);
    if(start_block<0){
        return address;
    }
    address = heap_block_to_address(heap, start_block);
    mark_heap_blocks_as_taken(heap, start_block, total_blocks);
    return address;
}

void heap_mark_blocks_free(struct heap *heap, uint32_t start_block){
    struct heap_table *table = heap->table;
    for(int i=start_block;i<(int)table->size;i++){
        HEAP_TABLE_ENTRY entry = table->table_entries[i];
        table->table_entries[i]=HEAP_TABLE_ENTRY_FREE;
        if(!(entry & HEAP_TABLE_ENTRY_HAS_NEXT)){
            break;
        }
    }
}



uint32_t heap_address_to_block(struct heap *heap, void *address){
    uint32_t ret = (uint32_t)(address - heap->start_addr)/HEAP_BLOACK_SIZE;
    return ret;
}

void *heap_malloc(struct heap *heap, size_t size){
    size_t aligned_size = heap_align_value(size);
    uint32_t total_blocks = aligned_size/HEAP_BLOACK_SIZE;
    return heap_allocate_blocks(heap,total_blocks);
}

void heap_free(struct heap *heap, void *ptr){
    heap_mark_blocks_free(heap,heap_address_to_block(heap,ptr));
    return;
}