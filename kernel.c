#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "ui.h"

void lau_main() {
    // Configura o manipulador para a exceção de divisão por zero (vetor 0)
    // --- DEBUG ---
    // Vamos testar apenas a saída de vídeo.
    vga_clear();
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_print("Kernel Iniciado!");

    while(1);
}
