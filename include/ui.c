#include "ui.h"
#include "vga.h"

void draw_terminal_ui() {
    vga_clear();
    vga_set_color(VGA_WHITE, VGA_BLACK);

    // Topo: ┌──[TasmaOS]
    vga_putchar_at(0, 0, 0xC9);  // ┌
    vga_putchar_at(1, 0, 0xCD);  // ─
    vga_putchar_at(2, 0, 0xCD);  // ─
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_putchar_at(3, 0, '[');
    vga_print_at(4, 0, "TasmaOS");
    vga_putchar_at(11, 0, ']');

    // Bottom: └──⊳
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_putchar_at(0, 2, 0xC8);  // └
    vga_putchar_at(1, 2, 0xCD);  // ─
    vga_putchar_at(2, 2, 0xCD);  // ─
    vga_set_color(VGA_GREEN, VGA_BLACK);
    vga_putchar_at(3, 2, 0x19);  // ⊳

    // Posiciona o cursor para a entrada do usuário
    vga_set_cursor(4, 2);
    vga_set_color(VGA_WHITE, VGA_BLACK);
}