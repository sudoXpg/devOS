#include "headers/kernel.h"

extern void problem();

void kernel_start(){

    terminal_init();
    idt_init();

    print("hello world!\ndevOS\n");
    problem();
}