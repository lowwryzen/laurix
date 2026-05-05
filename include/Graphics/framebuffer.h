#ifndef KERNEL_FRAMEBUFFER_H
#define KERNEL_FRAMEBUFFER_H
#include <utypes.h>

typedef struct {
    uint32_t addr;        // endereço físico do framebuffer
    uint32_t width;       // largura em pixels
    uint32_t height;      // altura em pixels
    uint32_t pitch;       // bytes por linha
    uint8_t  bpp;         // bits por pixel
    uint32_t size;        // size framebuffer
} __attribute__((packed)) framebuffer_info_t;

// LOCAL FIXO DOS DADOS DO FRAMEBUFFER
#define FB_INFO_ADDR 0x7000

// PEGA DIRETAMENTE A STRUCT
// ESCOPO DEFINIDO EM: /src/boot/vbe.asm
#define fb_info_addr ((framebuffer_info_t*)FB_INFO_ADDR)

#endif