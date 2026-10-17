#include "vga/vga.h"
#include "idt/idt.h"

void lau_main() {
    set_idt_entry(&ir0, (uint8_t)0x8E, (uint8_t)0);

    load_IDT();

    vga_print("Bomdia cidadaos");

    volatile int a = 10/0;
    a = 0;

    while(1);
}
