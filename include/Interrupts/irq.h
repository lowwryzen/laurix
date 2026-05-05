#ifndef IRQ_H
#define IRQ_H
#include "utypes.h"

typedef struct {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
    uint32_t eip, cs, eflags;                         // empilhados pela CPU
} __attribute__((packed)) irq_frame_t;

void irq_init(void);

#endif