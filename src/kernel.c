#include "headers/kernel.h"

static struct paging_4gb *kernel_paging =0;      // static so is only accessible here

void kernel_start(){

    terminal_init();
    
    idt_init();
    
    print("hello world!\ndevOS\n");
    
    kheap_init();

    kernel_paging = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    paging_switch(kernel_paging->directory_entry);  // switch to kernel paging chunk
    enable_paging();

    char buff[512];
    disk_read_sector(0,1,buff);

    __asm__("sti;");// enable interrupts after idt loaded


}