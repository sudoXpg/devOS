#include "disk.h"

struct disk disk;       // primary hdd

int disk_read_sector(int lba, int total_blocks, void *buffer){                  //https://wiki.osdev.org/ATA_PIO_Mode#:~:text=write%20command%20completes.-,48%20bit%20PIO,-Reading%20sectors%20using

    outb(0x1F6, (lba >> 24) | 0xE0);                                            // Send the high 4 bits of the LBA (Logical Block Address) and set the drive selection bit (0xE0 for master drive).
    outb(0x1F2, total_blocks);                                                  // Specify the number of sectors to read (total_blocks).
    outb(0x1F3, (unsigned char)(lba & 0xff));                                   // Send the low 8 bits of the LBA (bits 0-7).
    outb(0x1F4, (unsigned char)(lba >> 8));                                     // Send the next 8 bits of the LBA (bits 8-15).
    outb(0x1F5, (unsigned char)(lba >> 16));                                    // Send the next 8 bits of the LBA (bits 16-23).    
    outb(0x1F7, 0x20);                                                          // Send the command byte to initiate a read operation (0x20 for READ SECTORS command in 28-bit PIO mode).

    unsigned short *ptr = (unsigned short *)buffer;                             // 2bytes read together
    for(int i=0; i<total_blocks; i++) {
        char c = insb(0x1F7);
        while(!(c & 0x08)) {                                                    // Loop until the DRQ bit (bit 3) is set
            c = insb(0x1F7);
        }
        for(int i=0; i<256; i++) {                                              // 256*2(size of short) = sizeof sector
            *ptr = insw(0x1F0);                                                 // Read a 16-bit word from the data port
            ptr++;                                                              // Move to the next memory location in the buffer
        }
    }


    return 0;
}


// TODO -- implement later 
void disk_lookup_init(){
    memset(&disk, 0, sizeof(disk));
    disk.disk_type = DISK_TYPE_REAL;
    disk.sector_size = SECTOR_SIZE;
}

struct disk* disk_get(int index){
    if(index!=0){
        return 0;
    }
    return &disk;
}

int disk_read_block(struct disk* diskin, int lba, int total_blocks, void *buffer){
    if(diskin!=&disk){
        return ERROR_DISK_ERROR;
    }
    return disk_read_sector(lba,total_blocks,buffer);

}