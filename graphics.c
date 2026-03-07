#include "graphics.h"
#include "ports.h"

#define VGA_GRAPHICS_ADDR 0xA0000
#define VGA_WIDTH  320
#define VGA_HEIGHT 200

static uint8_t* vga_buffer = (uint8_t*)VGA_GRAPHICS_ADDR;

// Registradores VGA padrão para o Modo 13h (320x200x256)
static uint8_t mode_13h_regs[] = {
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00, 0x00
};

void vga_set_mode_13h() {
    uint8_t *regs = mode_13h_regs;
    unsigned int i;

    outb(0x3C2, *regs++); // MISC
    for(i = 0; i < 5; i++) { // SEQ
        outb(0x3C4, i);
        outb(0x3C5, *regs++);
    }
    outb(0x3D4, 0x03); // Select CRTC register 3
    outb(0x3D5, inb(0x3D5) | 0x80); // Read from data port, modify, and write back
    outb(0x3D4, 0x11); // CRTC Unlock
    outb(0x3D5, inb(0x3D5) & 0x7F); // Remove bit de proteção

    for(i = 0; i < 25; i++) { // CRTC
        outb(0x3D4, i);
        outb(0x3D5, *regs++);
    }
    for(i = 0; i < 9; i++) { // GC
        outb(0x3CE, i);
        outb(0x3CF, *regs++);
    }
    for(i = 0; i < 21; i++) { // AC
        inb(0x3DA); // Reset flip-flop
        outb(0x3C0, i);
        outb(0x3C0, *regs++);
    }
    inb(0x3DA);
    outb(0x3C0, 0x20); // Enable video
}

void vga_put_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        vga_buffer[y * VGA_WIDTH + x] = color;
    }
}

void vga_clear_screen(uint8_t color) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) vga_buffer[i] = color;
}