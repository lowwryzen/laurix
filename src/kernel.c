#include "vga/vga.h"
#include "idt/idt.h"

#include "shell/shell.h"

extern void pic_remap();

void lau_main() {
    set_idt_entry(&ir0, (uint8_t)0x8E, (uint8_t)0);
    set_idt_entry(&ir21, (uint8_t)0x8E, (uint8_t)0x21);

    load_IDT();

    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_println("Welcome to laurix");

    pic_remap();
    asm("sti");

    init_shell();
}
