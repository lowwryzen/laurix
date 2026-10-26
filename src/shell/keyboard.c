#include "shell/keyboard.h"

bool enter;

volatile uint8_t scan_table[127] = {
    [0x39] = ' ',

    [0x0B] = '0', [0x2] = '1', [0x3] = '2',
    [0x04] = '3', [0x5] = '4', [0x6] = '5',
    [0x7] = '6', [0x8] = '7', [0x9] = '8',
    [0x0A] = '9',

    [0x1E] = 'a', [0x30] = 'b', [0x2E] = 'c',
    [0x20] = 'd', [0x12] = 'e', [0x21] = 'f',
    [0x22] = 'g', [0x23] = 'h', [0x17] = 'i',
    [0x24] = 'j', [0x25] = 'k', [0x26] = 'l',
    [0x32] = 'm', [0x31] = 'n', [0x18] = 'o',
    [0x19] = 'p', [0x10] = 'q', [0x13] = 'r',
    [0x1F] = 's', [0x14] = 't', [0x16] = 'u',
    [0x2F] = 'v', [0x11] = 'w', [0x2D] = 'x',
    [0x15] = 'y', [0x2C] = 'z'
};

void read_key(uint8_t key){
    enter = 0;

    if (scan_table[key] && key < 127)
        vga_putchar(scan_table[key]);

    if (key == 0x1C){
        enter = 1;
        vga_putchar('\0');
        return;
    }
    if (key == 0x0E){
        vga_clean(1);
        return;
    }

}