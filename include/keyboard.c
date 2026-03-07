#include "keyboard.h"
#include "vga.h"
#include "ports.h"
#include "pic.h"

void keyboard_handler() {
    // Lê o scancode da porta de dados do teclado
    uint8_t scancode = inb(0x60);

    // Por enquanto, apenas imprime uma mensagem para mostrar que funcionou
    vga_print("Key pressed! ");

    // Envia o sinal de "End-of-Interrupt" para o PIC
    pic_send_eoi(1);
}