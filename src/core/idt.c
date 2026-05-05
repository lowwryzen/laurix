#include <Interrupts/idt.h>

static idt_entry_t idt[256];
static idt_ptr_t   idt_ptr;

extern void isr0(void);

void idt_set_gate(uint8_t num, uint32_t handler)
{
    idt[num].base_low  = handler & 0xFFFF;
    idt[num].selector  = 0x08;
    idt[num].zero      = 0;
    idt[num].flags     = 0x8E;
    idt[num].base_high = (handler >> 16) & 0xFFFF;
}

/**
 * @brief COnfigura o sistema da IDT.
 */
void idt_init(void)
{
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base  = (uint32_t)&idt;

    idt_set_gate(0, (uint32_t)isr0);

    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
}
/**
 * @brief Inicia o sistema da IDT.
 * @warning Habilita interrupcoes (STI) apos configuracão!
 *          Certifique-se que todos os handlers necessarios
 *          estao registrados antes de chamar esta funcao.
 */
void idt_start()
{
    __asm__ volatile("sti");
}

void isr0_handler(void)
{
    volatile char *vga = (volatile char*)0xB8000;
    const char *msg = "EXCEPTION: Division By Zero!";

    // TELINHA DE DIVISION BY ZERO
    //  CODIGO TESTE
    int i = 0;
    while (msg[i]) {
        vga[i*2]   = msg[i];
        vga[i*2+1] = 0x4F;
        i++;
    }

    for(;;) __asm__ volatile("hlt");
}