; ============================================
; CONSTANTES
; ============================================
KERNEL_SEGMENT  equ 0x1000
KERNEL_OFFSET   equ 0x0000
CODE_SEG        equ 0x08
DATA_SEG        equ 0x10

BOOT_INFO_HEADER equ 0x4000 
BOOT_INFO_HEADER_MAGIC equ 0xFFDDFFDF

FB_INFO_ADDR    equ 0x7000
VBE_INFO_ADDR   equ 0x6000   ; buffer fora do bootloader
VBE_MODE_ADDR   equ 0x6200   ; buffer fora do bootloader

MEMMAP_ADDR equ 0x8000
MEMMAP_MAGIC equ 0x4D4D4150 ; "MMAP"