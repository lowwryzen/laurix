#include "vga/vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t* const vga = (uint16_t*)0xB8000;
static uint8_t current_color = (VGA_RED | (VGA_BLACK << 4));

static uint16_t cursor;

uint16_t get_current_vga(){
    return cursor;
}

void vga_set_color(uint8_t fg, uint8_t bg) {
    current_color = fg | (bg << 4);
}

void vga_putchar(char c) {
    vga[cursor++] = (current_color << 8) | c;

    if (cursor >= VGA_WIDTH * VGA_HEIGHT) {
        cursor = 0; // simples por enquanto
    }
}

void vga_print(const char* s) {
    for (int i = 0; s[i]; i++) {
        vga_putchar(s[i]);
    }
}

void vga_println(const char* s){
    vga_print(s);
    cursor = ((cursor + (VGA_WIDTH-1)*2) / (VGA_WIDTH*2)) * (VGA_WIDTH*2);
}

void vga_clean(uint16_t back){
    if (cursor > 0)
        vga[--cursor] = VGA_BLACK | (VGA_BLACK << 8);
}
