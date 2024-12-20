#ifndef KERNEL_H
#define KERNEL_H

#include "constants.h"
#include "colors.h"
#include "../string/string.h"
#include "../display/display.h"
#include "../idt/idt.h"
#include "../io/io.h"
#include "../memory/heap/kheap.h"
#include "../memory/paging/paging.h"
#include "../disk/disk.h"

#include<stdint.h>

void kernel_start();


#endif