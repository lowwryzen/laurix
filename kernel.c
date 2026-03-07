#include "vga.h"
#include "idt.h"
#include "pic.h"
#include "ui.h"
#include "shell.h"

void lau_main() {
    // Configura o manipulador para a exceção de divisão por zero (vetor 0)
    set_idt_entry(&ir0, (uint8_t)0x8E, (uint8_t)0);

    // Configura o manipulador para General Protection Fault (vetor 13)
    set_idt_entry(&ir13, (uint8_t)0x8E, (uint8_t)13);

    // Remapeia o PIC para que os IRQs comecem no vetor 32
    pic_remap();

    // Ativa apenas a interrupção do teclado (IRQ 1)
    pic_enable_irq(1);

    // Configura o manipulador para o teclado (IRQ 1 -> vetor 33)
    set_idt_entry(&irq1_handler, (uint8_t)0x8E, (uint8_t)33);

    load_IDT();

    shell_init();

    asm("sti"); // Ativa as interrupções

    while(1);
}
