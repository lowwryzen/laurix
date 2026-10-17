#include "interrupt/handler.h"

void division_error_handler(){
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    vga_print("Zero Division Error");

    asm("hlt");
}