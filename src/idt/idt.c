#include "idt/idt.h"
#include "vga/vga.h"

volatile uint16_t idt_entries[256][4];
volatile uint16_t idtr[2];

void load_IDT(){
    uint32_t addr = (uint32_t)idt_entries;

    idtr[0] = 256*8-1;
    idtr[1] = (uint16_t)addr;
    idtr[2] = (uint16_t)(addr >> 16);

    asm("lidt %[idtr]" : : [idtr] "m" (idtr));
}

void set_idt_entry(void *isr, uint8_t flags, uint8_t index){
    volatile uint32_t addr = (uint32_t)isr;

    idt_entries[index][BASE_ADDR]       = (uint16_t) addr;
    idt_entries[index][SEGMENT]         = (uint16_t) KERNEL_CS;
    idt_entries[index][NULL_AND_FLAGS]  = (uint16_t) (flags << 8 | (uint8_t)0);
    idt_entries[index][HIGH_ADDR]       = (uint16_t) (addr >> 16);
}