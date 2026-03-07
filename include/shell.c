#include "shell.h"
#include "vga.h"
#include "ui.h"

#define CMD_BUFFER_SIZE 128
static char cmd_buffer[CMD_BUFFER_SIZE];
static int cmd_pos = 0;

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void shell_init() {
    vga_clear();
    vga_set_color(VGA_GREEN, VGA_BLACK);
    vga_print("TasmaOS Shell v1.0\n");
    vga_print("Digite 'help' para comandos disponiveis\n");
    vga_print("> ");
    cmd_pos = 0;
}

void enter_gui_mode() {
    draw_terminal_ui();
    // Em um sistema real, aqui entrariamos em um loop de eventos da GUI
    // Por enquanto, apenas desenhamos a UI estática
}

void execute_command(const char* cmd) {
    vga_print("\n"); // Pula linha após o Enter

    if (strcmp(cmd, "help") == 0) {
        vga_print("Comandos disponiveis:\n");
        vga_print("  help   - Mostra esta ajuda\n");
        vga_print("  clear  - Limpa a tela\n");
        vga_print("  gui    - Entra na interface grafica (UI)\n");
        vga_print("  about  - Sobre o TasmaOS\n");
    } else if (strcmp(cmd, "clear") == 0) {
        vga_clear();
    } else if (strcmp(cmd, "gui") == 0) {
        enter_gui_mode();
        return; // Não imprime o prompt novamente imediatamente se mudar a tela
    } else if (strcmp(cmd, "about") == 0) {
        vga_print("TasmaOS - Sistema Operacional Bare-metal x86\n");
        vga_print("Desenvolvido como projeto educacional\n");
    } else if (cmd[0] != '\0') {
        vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
        vga_print("Comando nao encontrado: ");
        vga_print(cmd);
        vga_print("\n");
        vga_set_color(VGA_GREEN, VGA_BLACK);
    }

    vga_print("> ");
}

void shell_input(char c) {
    if (c == '\n') {
        cmd_buffer[cmd_pos] = '\0';
        execute_command(cmd_buffer);
        cmd_pos = 0;
    } else if (c == '\b') {
        if (cmd_pos > 0) {
            cmd_pos--;
            vga_putchar('\b'); // O vga.c atualizado lidará com o visual
        }
    } else if (c >= 32 && c < 127 && cmd_pos < CMD_BUFFER_SIZE - 1) {
        cmd_buffer[cmd_pos++] = c;
        vga_putchar(c);
    }
}