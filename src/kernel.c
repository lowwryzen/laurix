/*
    KERNEL MAIN
*/

#include <Graphics/framebuffer.h>
#include <BiosData/mmap.h>

#include <Interrupts/irq.h>
#include <Interrupts/idt.h>

#include <Graphics/vga.h>
#include <pic.h>

#include <serial.h>

/**
 * @brief Configura o PIC antes de carregar a IDT.
 * @warning Deve ser chamado ANTES de idt_init() e STI.
 */
static inline void setup_pic()
{
    pic_remap();
    serial_print("PIC Configurado!\n");
}

void lau_main()
{
    serial_init();
    serial_print("Serial COM1 OK!\n");

    setup_pic();
    idt_init();
    irq_init();
    idt_start();

    memmap_header_t* memory_map = memory_header_info_addr;
    if (memory_map->magic != MMAP_MAGIC) {
        serial_print("Magic Invalido!\n");
        while(1);
    }
    e820_entry_t* map = (e820_entry_t*)(MMAP_ADDR + sizeof(memmap_header_t));
    for (int i = 0; i < memory_map->count; i++) {
        e820_entry_t* entry = &map[i];
        if (entry->type == 1) {
            serial_print("Memoria Livre!\n");
        }
    }

    serial_print("Laurix Iniciado!\n");
    while(1);
}