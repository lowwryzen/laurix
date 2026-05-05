[BITS 16]
[ORG 0x7C00]

%include "src/boot/configure/defines.inc"

; ============================================
; ENTRY POINT
; ============================================
start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov [boot_drive], dl

    call enable_a20
    call load_kernel

    ;call setup_vbe ; Orginalmente Desativado!
    call memory_map

    lgdt [gdt_descriptor]

    mov eax, cr0
    or  eax, 1
    mov cr0, eax

    jmp CODE_SEG:protected_mode_entry

; ============================================
; MÓDULOS
; ============================================
%include "src/boot/a20.asm"

%include "src/boot/disk.asm"
%include "src/boot/vbe.asm"
%include "src/boot/memory_map.asm"

%include "src/boot/gdt.asm"
%include "src/boot/pm_enter.asm"

; ============================================
; PADDING BIOS
; ============================================
times 510 - ($ - $$) db 0
dw 0xAA55