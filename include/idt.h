#ifndef IDT_H
#define IDT_H

#include "utypes.h"
#include "vga.h"

extern void load_IDT();
extern void set_idt_entry(void *isr, uint8_t flags, uint8_t index);

extern void ir0();
extern void irq1_handler();

void division_error_handler();


#endif