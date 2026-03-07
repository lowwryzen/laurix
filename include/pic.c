#include "pic.h"
#include "ports.h"

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define ICW1_ICW4       0x01
#define ICW1_INIT       0x10
#define ICW4_8086       0x01

void pic_remap() {
    // Inicia a sequência de inicialização (em modo cascata)
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // Define os offsets dos vetores da IDT (Master: 32-39, Slave: 40-47)
    outb(PIC1_DATA, 32);
    outb(PIC2_DATA, 40);

    // Informa ao Master que há um Slave na IRQ2 (0000 0100)
    outb(PIC1_DATA, 4);
    // Informa ao Slave sua identidade na cascata (0000 0010)
    outb(PIC2_DATA, 2);

    // Define o modo 8086
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // Limpa as máscaras (ativa todas as IRQs)
    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 0);
}

void pic_send_eoi(unsigned char irq) {
    if(irq >= 8) {
        outb(PIC2_COMMAND, 0x20); // Envia EOI para o Slave
    }
    outb(PIC1_COMMAND, 0x20); // Envia EOI para o Master
}