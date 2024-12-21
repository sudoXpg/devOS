#ifndef DISK_H
#define DISK_H

#include "../io/io.h"
#include "../memory/memory.h"
#include "../headers/constants.h"

typedef int DISK_TYPE;

// physical drive
#define DISK_TYPE_REAL 0

struct disk{
    DISK_TYPE disk_type;
    int sector_size;

};


void disk_lookup_init();
int disk_read_block(struct disk* diskin, int lba, int total_blocks, void *buffer);
struct disk* disk_get(int index);



#endif