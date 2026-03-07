#include "idt.h"

void division_error_handler(){
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    vga_print("Zero Division Error");

    asm("hlt");
}

void general_protection_fault_handler() {
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    vga_print("General Protection Fault");
    asm("hlt");
}

void page_fault_handler() {
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    vga_print("Page Fault");
    asm("hlt");
}