[BITS 16]

%include "src/boot/configure/defines.inc"

setup_vbe:
    pusha

    ; 1. Verifica VBE
    mov ax, 0x4F00
    mov di, VBE_INFO_ADDR
    int 0x10
    cmp ax, 0x004F
    jne .error

    ; 2. Pega info do modo 1024x768 32bpp
    mov ax, 0x4F01
    mov cx, 0x0118
    mov di, VBE_MODE_ADDR
    int 0x10
    cmp ax, 0x004F
    jne .error

    ; 3. Ativa o modo
    mov ax, 0x4F02
    mov bx, 0x4118
    int 0x10
    cmp ax, 0x004F
    jne .error

    mov edi, FB_INFO_ADDR

    ; Addr Framebuffer
    mov eax, [VBE_MODE_ADDR + 40]  ; PhysBasePtr
    mov [edi + 0], eax

    ; width
    movzx eax, word [VBE_MODE_ADDR + 18]  ; XResolution
    mov [edi + 4], eax

    ; height
    movzx eax, word [VBE_MODE_ADDR + 20]  ; YResolution
    mov [edi + 8], eax

    ; pitch
    movzx eax, word [VBE_MODE_ADDR + 16]  ; BytesPerScanLine
    mov [edi + 12], eax

    ; bpp
    mov al, [VBE_MODE_ADDR + 25]   ; BitsPerPixel
    mov [edi + 16], al

    ; size calc
    mov eax, [VBE_MODE_ADDR + 16] ; pitch
    movzx ebx, word [VBE_MODE_ADDR + 20] ;height
    imul eax, ebx
    mov [edi + 20], eax

    popa
    ret

.error:
    mov si, msg_vbe_error
    call print_string
    jmp $

msg_vbe_error: db "VBE error!", 13, 10, 0