#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t* const vga = (uint16_t*)0xB8000;
static uint8_t current_color = (VGA_RED | (VGA_BLACK << 4));

static uint16_t cursor;

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

void vga_putchar_at(int x, int y, char c) {
    int pos = y * VGA_WIDTH + x;
    if (pos >= 0 && pos < VGA_WIDTH * VGA_HEIGHT) {
        vga[pos] = (current_color << 8) | (uint8_t)c;
    }
}

void vga_print_at(int x, int y, const char* s) {
    int old_cursor = cursor;
    cursor = y * VGA_WIDTH + x;
    vga_print(s);
    cursor = old_cursor;
}

void vga_clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = (VGA_BLACK << 12) | ' ';
    }
    cursor = 0;
}

void vga_set_cursor(int x, int y) {
    cursor = y * VGA_WIDTH + x;
}
