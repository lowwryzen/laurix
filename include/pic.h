#ifndef KERNEL_PIC_CONFIGURE_H
#define KERNEL_PIC_CONFIGURE_H

// PORTAS PIC
#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

#define PIC_EOI   0x20   // End Of Interrupt

void pic_remap(void);
void pic_mask();
void pic_signal();

#endif