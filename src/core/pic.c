#include <pic.h>

#include <utypes.h>

// IO OUTB
static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void pic_remap(void)
{
    // Inicializa os dois PICs
    outb(PIC1_CMD,  0x11);  // ICW1: iniciar
    outb(PIC2_CMD,  0x11);
    outb(PIC1_DATA, 0x20);  // ICW2: IRQ0-7  → vetores 0x20-0x27
    outb(PIC2_DATA, 0x28);  // ICW2: IRQ8-15 → vetores 0x28-0x2F
    outb(PIC1_DATA, 0x04);  // ICW3: PIC1 tem PIC2 no IR2
    outb(PIC2_DATA, 0x02);  // ICW3: PIC2 cascateado no IR2
    outb(PIC1_DATA, 0x01);  // ICW4: modo 8086
    outb(PIC2_DATA, 0x01);
}
void pic_mask()
{
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}
void pic_signal()
{
    outb(PIC1_CMD, PIC_EOI);
}