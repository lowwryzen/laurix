#ifndef PIC_H
#define PIC_H

void pic_remap();
void pic_send_eoi(unsigned char irq);

#endif