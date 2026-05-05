%include "src/boot/configure/defines.inc"

load_kernel:
    pusha
    mov si, dap
    mov dl, [boot_drive]
    mov ah, 0x42
    int 0x13
    jc .error
    popa
    ret
.error:
    mov si, msg_load_error
    call print_string
    jmp $

print_string:
    pusha
    mov ah, 0x0E
.loop:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    popa
    ret

boot_drive:      db 0
msg_load_error:  db "Kernel load error!", 13, 10, 0

align 4
dap:
    db 0x10
    db 0x00
    dw 8
    dw KERNEL_OFFSET
    dw KERNEL_SEGMENT
    dq 1