#include "interrupt/handler.h"

void division_error_handler(){
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    vga_print("Zero Division Error");

    asm("hlt");
}

void keyboard_handler(){
    vga_set_color(VGA_WHITE, VGA_BLACK);
    uint8_t key;

    asm(
        "inb $0x60, %%al\n"
        "movb %[key_pressed], %%al"
        : [key_pressed] "=r" (key)
        : 
    );

    vga_putchar(key+65-28);
}