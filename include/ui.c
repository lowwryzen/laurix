#include "ui.h"
#include "vga.h"

void draw_box_top(int x, int y, int width, const char* title) {
    vga_set_color(VGA_WHITE, VGA_BLACK);
    
    // Canto superior esquerdo
    vga_putchar_at(x, y, 0xC9);  // ┌
    
    // Linha horizontal
    for (int i = 1; i < width - 1; i++) {
        vga_putchar_at(x + i, y, 0xCD);  // ─
    }
    
    // Canto superior direito
    vga_putchar_at(x + width - 1, y, 0xBB);  // ┐
    
    // Título
    if (title) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        // Usamos set_cursor para garantir que o texto flua corretamente
        vga_set_cursor(x + 2, y);
        vga_print("[");
        vga_print(title);
        vga_print("]");
    }
}

void draw_box_bottom(int x, int y, int width) {
    vga_set_color(VGA_WHITE, VGA_BLACK);
    
    // Canto inferior esquerdo
    vga_putchar_at(x, y, 0xC8);  // └
    
    // Linha horizontal
    for (int i = 1; i < width - 1; i++) {
        vga_putchar_at(x + i, y, 0xCD);  // ─
    }
    
    // Canto inferior direito
    vga_putchar_at(x + width - 1, y, 0xBC);  // ┘
    
    // Prompt
    vga_set_color(VGA_GREEN, VGA_BLACK);
    vga_putchar_at(x + width - 3, y, 0x19);  // ⊳ (Seta para baixo/direita ou similar em CP437)
}

void draw_terminal_ui() {
    // Limpa tela
    vga_clear();
    
    // Desenha topo da janela
    draw_box_top(0, 0, 80, "TasmaOS"); // Largura 80 para preencher a tela
    
    // Desenha linha do prompt (ajustado para baixo para dar espaço)
    draw_box_bottom(0, 2, 80);
    
    // Posiciona cursor para input
    vga_set_cursor(3, 2);
    vga_set_color(VGA_WHITE, VGA_BLACK); // Reseta cor para digitação
}