#include "keyboard.h"
#include "ports.h"
#include "pic.h"
#include "vga.h"
#include "utypes.h"
#include "shell.h"

// Mapeamento básico de scancode (US QWERTY) para ASCII.
static const char scancode_to_ascii_map[128] = {
    0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t','q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'','`',
    0,  '\\','z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
    '*', 0,   ' ', 0
};

// Função auxiliar para converter scancode para ASCII
static char scancode_to_ascii(uint8_t scancode) {
    if (scancode < 128) {
        return scancode_to_ascii_map[scancode];
    }
    return 0;
}

void keyboard_handler() {
    // Lê o scancode da porta de dados do teclado
    uint8_t scancode = inb(0x60);

    char c = scancode_to_ascii(scancode);
    if (c) {
        shell_input(c);
    }

    pic_send_eoi(1); // Envia EOI para a IRQ 1 (teclado)
}