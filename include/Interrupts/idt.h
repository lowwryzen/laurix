#ifndef IDT_H
#define IDT_H
#include "utypes.h"

typedef struct {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_gate(uint8_t num, uint32_t handler);
void idt_init(void);
void idt_start();

#endif