[BITS 32]

%include "src/boot/configure/defines.inc"

protected_mode_entry:
    mov ax, DATA_SEG

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    ; 0x1000 * 16 + 0x0000 = 0x10000
    jmp CODE_SEG:(KERNEL_SEGMENT * 16 + KERNEL_OFFSET)