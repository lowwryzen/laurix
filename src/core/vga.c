#include <Graphics/vga.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t* const vga = (uint16_t*)0xB8000;
static uint8_t current_color = (VGA_RED | (VGA_BLACK << 4));
static uint16_t cursor;

void vga_set_color(uint8_t fg, uint8_t bg) {
    current_color = fg | (bg << 4);
}

void vga_putchar(char c) {
    if (c == '\n') {
        // QUEBRA DE LINHA
        cursor += VGA_HEIGHT - (cursor % VGA_WIDTH);
    } else {
        vga[cursor++] = (current_color << 8) | c;
    }

    // FIM DA TELA, RETORNA AO INICIO!
    if (cursor >= VGA_WIDTH * VGA_HEIGHT) {
        cursor = 0;
    }
}

void vga_print(const char* s) {
    for (int i = 0; s[i]; i++) {
        vga_putchar(s[i]);
    }
}