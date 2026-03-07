#ifndef VGA_H
#define VGA_H

#include "utypes.h"

enum vga_color {
    VGA_BLACK = 0x0,
    VGA_BLUE = 0x1,
    VGA_GREEN = 0x2,
    VGA_CYAN = 0x3,
    VGA_RED = 0x4,
    VGA_MAGENTA = 0x5,
    VGA_BROWN = 0x6,
    VGA_LIGHT_GREY = 0x7,
    VGA_DARK_GREY = 0x8,
    VGA_LIGHT_BLUE = 0x9,
    VGA_LIGHT_GREEN = 0xA,
    VGA_LIGHT_CYAN = 0xB,
    VGA_LIGHT_RED = 0xC,
    VGA_LIGHT_MAGENTA = 0xD,
    VGA_YELLOW = 0xE,
    VGA_WHITE = 0xF,
};

void vga_set_color(uint8_t fg, uint8_t bg);
void vga_putchar(char c);
void vga_print(const char* s);
void vga_putchar_at(int x, int y, char c);
void vga_print_at(int x, int y, const char* s);
void vga_clear();
void vga_set_cursor(int x, int y);

#endif
