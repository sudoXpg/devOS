#include "kheap.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init(){
    int total_table_entries = HEAP_SIZE_BYTES/HEAP_BLOACK_SIZE;
    kernel_heap_table.table_entries = (HEAP_TABLE_ENTRY *) HEAP_TABLE_START_ADDRESS;
    kernel_heap_table.size=total_table_entries;

    void *end = (void *) (HEAP_START_ADDRESS+HEAP_SIZE_BYTES);
    int ret = create_heap(&kernel_heap,(void*)HEAP_START_ADDRESS,end, &kernel_heap_table);
    if(ret<0){
        print("\nFAILED TO CREATE HEAP\n");
    }
}

void *kmalloc(size_t size){
    return heap_malloc(&kernel_heap,size);
}

void kfree(void *ptr){
    heap_free(&kernel_heap, ptr);
    return;
}

void *kzalloc(size_t size){
    void *ptr = kmalloc(size);
    if(!ptr){
        return 0;
    }
    memset(ptr,0,size);
    return ptr;
}