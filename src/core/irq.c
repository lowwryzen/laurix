#include <Interrupts/irq.h>
#include <Interrupts/idt.h>

#include <pic.h>

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

extern void irq0(void); // EXTERN

/**
 * @brief Registra o IRQ0 na IDT e habilita o timer no PIC.
 * @warning Deve ser chamado apos idt_init().
 */
void irq_init(void) {
    // Registra IRQ0 no vetor 0x20
    idt_set_gate(0x20, (uint32_t)irq0);
    // Desmascara apenas o IRQ0 (bit 0 = 0 = habilitado)
    outb(PIC1_DATA, 0xFE);
}

static uint32_t ticks = 0;
/**
 * @brief Handler do timer — captura o frame da CPU a cada tick.
 * @param frame Ponteiro para o estado dos registradores.
 */
void irq0_handler(irq_frame_t *frame) {
    ticks++;

    // DELAY
    if (ticks % 18 != 0) {
        pic_signal();
        return;
    }

    volatile uint16_t *vga = (volatile uint16_t*)0xB8000;
    int pos = 0;

    // Helper local pra printar hex
    const char *hex = "0123456789ABCDEF";

    vga[pos++] = (0x0A << 8) | 'E';
    vga[pos++] = (0x0A << 8) | 'I';
    vga[pos++] = (0x0A << 8) | 'P';
    vga[pos++] = (0x0A << 8) | ':';

    for (int i = 28; i >= 0; i -= 4) vga[pos++] = (0x0A << 8) | hex[(frame->eip >> i) & 0xF];

    vga[pos++] = (0x0A << 8) | ' ';

    vga[pos++] = (0x0E << 8) | 'C';
    vga[pos++] = (0x0E << 8) | 'S';
    vga[pos++] = (0x0E << 8) | ':';

    for (int i = 28; i >= 0; i -= 4) vga[pos++] = (0x0E << 8) | hex[(frame->cs >> i) & 0xF];

    vga[pos++] = (0x0E << 8) | ' ';

    vga[pos++] = (0x0C << 8) | 'F';
    vga[pos++] = (0x0C << 8) | 'L';
    vga[pos++] = (0x0C << 8) | ':';

    for (int i = 28; i >= 0; i -= 4) vga[pos++] = (0x0C << 8) | hex[(frame->eflags >> i) & 0xF];

    // SINAL PIC
    pic_signal();
}