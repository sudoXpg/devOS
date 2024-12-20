#include "headers/kernel.h"


void kernel_start(){

    terminal_init();
    idt_init();

    print("hello world!\ndevOS\n");
    kheap_init();
    
}