#include "idt.h"


struct idt idt_table[TOTAL_INTS];
struct idtr idtr_descriptor;

extern void idt_load(struct idtr *ptr);



void idt_zero(){
    print("int 0\n");
}


void set_idt(int int_num, void *address){
    struct idt* descriptor = &idt_table[int_num];
    descriptor->offset_1 = (uint32_t)address & 0x0000ffff;
    descriptor->selector= CODE_SELECTOR;
    descriptor->zero=0x00;
    descriptor->type_attributes=0xEE;                           // 32bit interrupt mode
    descriptor->offset_2 = (uint32_t)address >> 16;
}

void idt_init(){
    memset(idt_table,0,sizeof(idt_table));

    // setup the IDTR
    idtr_descriptor.limit=sizeof(idt_table)-1;
    idtr_descriptor.base=(uint32_t)idt_table;
    
    // set the interrupt
    set_idt(32,idt_zero);
    
    // load the interrupt using ASM
    idt_load(&idtr_descriptor);
}
