#ifndef CONSTANTS_H
#define CONSTANTS_H

#include"status.h"

#define VIDEO_MEMORY_START 0xB8000

#define VGA_HEIGHT 25
#define VGA_WIDTH 80

#define TOTAL_INTS 512

#define CODE_SELECTOR 0x08
#define DATA_SELECTOR 0x10

#define HEAP_SIZE_BYTES 104857600                   // 100MB in bytes 100*1024*1024
#define HEAP_BLOACK_SIZE 4096                       // 4KB is min memory that can be allocated
#define HEAP_START_ADDRESS 0x01000000	            // from memory map https://wiki.osdev.org/Memory_Map_(x86)#:~:text=15%2D16MB%203-,0x01000000,-%3F%3F%3F%3F%3F%3F%3F%3F
#define HEAP_TABLE_START_ADDRESS 0x00007E00         // https://wiki.osdev.org/Memory_Map_(x86)#:~:text=Your%20OS%20BootSector-,0x00007E00,-0x0007FFFF

#define SECTOR_SIZE 512                             // default sector size of hdd

#define MAX_FILE_PATH 100

#endif