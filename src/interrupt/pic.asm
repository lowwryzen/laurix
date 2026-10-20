PIC_MASTER equ 0x20
PIC_SLAVE equ 0xA0

MASTER_DATA equ 0x21
SLAVE_DATA equ 0xA1

MASTER_OFFSET equ 0x20
SLAVE_OFFSET equ 0x28

global pic_remap

pic_remap:
    mov al, 0x11

    ; ICW 1
    out PIC_MASTER, al
    out PIC_SLAVE, al

    ; ICW 2
    mov al, MASTER_OFFSET
    out MASTER_DATA, al

    mov al, SLAVE_OFFSET
    out SLAVE_DATA, al

    ; ICW 3
    mov al, 1
    shl al, 2

    out MASTER_DATA, al
    mov al, 2
    out SLAVE_DATA, al

    ; ICW 4
    mov al, 1

    out MASTER_DATA, al
    out SLAVE_DATA, al

    mov al, 0

    out MASTER_DATA, al
    out SLAVE_DATA, al

    ; Only IRQ1
    mov al, 0b11111101
    out MASTER_DATA, al

    mov al, 0xFF
    out SLAVE_DATA, al

    ret