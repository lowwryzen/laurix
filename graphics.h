#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "utypes.h"

void vga_set_mode_13h();
void vga_put_pixel(int x, int y, uint8_t color);
void vga_clear_screen(uint8_t color);

#endif