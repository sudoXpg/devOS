#ifndef IDT_H
#define IDT_H

#include<stddef.h>
#include<stdint.h>

#include "../headers/constants.h"
#include "../memory/memory.h"
#include "../display/display.h"


// offset is the entry point of the ISR
struct idt{
    uint16_t offset_1;        // offset bits 0..15
    uint16_t selector;        // a code segment selector in GDT or LDT
    uint8_t  zero;            // unused, set to 0
    uint8_t  type_attributes; // gate type, dpl, and p fields
    uint16_t offset_2;        // offset bits 16..31
}__attribute__((packed));

struct idtr{
    uint16_t limit;         // length of IDT-1
    uint32_t base;          // address of IDT
}__attribute__((packed));


void idt_init();
void set_idt(int int_num, void *address);

#endif