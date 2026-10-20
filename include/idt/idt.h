#include "utils/utypes.h"

#define KERNEL_CS 0x08

extern void ir0();
extern void ir21();

typedef enum {
    BASE_ADDR = 0,
    SEGMENT = 1,
    NULL_AND_FLAGS = 2,
    HIGH_ADDR = 3
} IDT_ENTRY_OFFSET;

void load_IDT();
void set_idt_entry(void *isr, uint8_t flags, uint8_t index);

void division_error_handler();
void keyboard_handler();