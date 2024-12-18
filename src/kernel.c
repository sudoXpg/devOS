#include "headers/kernel.h"


void kernel_start(){

    terminal_init();
    idt_init();

    print("hello world!\ndevOS\n");
    outb(0x80,0x11);
}