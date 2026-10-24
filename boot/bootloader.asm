[BITS 16]
[ORG 0x7C00]

KERNEL_LOCATION equ 0x1000
DATA_SEG equ 0x10
CODE_SEG equ 0x08

start:
    cli
    mov [boot_drive], dl

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    in al, 0x92
    or al, 00000010b
    out 0x92, al

    call clear_screen

mov ah, 0x41
mov dl, [boot_drive]
mov bx, 0x55AA

int 0x13
jc load_kernel_floppy

load_kernel:
    mov si, dap

    mov dl, [boot_drive]
    mov ah, 0x42
    int 0x13
    jc load_kernel_error

    mov si, load_successful
    call println
    call sleep

    jmp activate_protected_mode

load_kernel_floppy:
    mov si, not_lba_msg
    call println
    call sleep

    xor di, di
    mov si, KERNEL_LOCATION

    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]
    xor bx, bx        
    mov es, bx

    mov byte[sector_count], 4

    read_loop:
        cmp di, [sector_count]
        je read_end

        mov ah, 0x02
        mov al, 1
        mov ch, 0
        mov bx, si
        int 0x13

        inc di
        add si, 512
        inc cl

        jmp read_loop

    read_end:
        mov si, load_successful
        call println
        call sleep

        jmp activate_protected_mode

activate_protected_mode:
    mov si, init_gdt_msg
    call println
    call sleep

    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:protected_mode_entry

gdt_start:
    dq 0

gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

dap:
    db 0x10        ; size
    db 0
    dw 2           ; sector
    dw KERNEL_LOCATION
    dw 0x0000
    dq 1           ; LBA sector

[BITS 32]
protected_mode_entry:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000
    jmp KERNEL_LOCATION

[BITS 16]

load_kernel_error:
    mov si, load_error_msg
    call println
    
    mov si, error_code_msg
    call println

    mov al, ah

    mov ah, 0x0E
    int 0x10
    jmp $

println:
    mov bx, 0

    loop:
        mov al, byte [si]
        
        cmp al, 0
        je newline
        
        mov ah, 0x0E
        int 0x10

        inc si
        jmp loop
        
    newline:
        mov al, 0x0D
        int 0x10

        mov al, 0x0A
        int 0x10

    ret

clear_screen:
    mov ah, 0x07
    mov al, 0x0
    mov bh, 0x07
    mov cx, 0x0
    mov dh, 24
    mov dl, 79
    int 0x10

    mov ah, 0x02
    mov bh, 0x0
    mov dx, 0x0
    int 0x10

    ret

sleep:
    mov ah, 0x86
    
    ; temporary aproximated 1 second

    mov cx, 0x000F ; high 1 second
    mov dx, 0x4240 ; lower 1 second
    
    int 0x15

    ret

boot_drive db 0
sector_count db 0

load_error_msg db "Unable to load laurix kernel", 0
not_lba_msg db "LBA not supported", 0

load_successful db "laurix kernel loaded sucessfully", 0
init_gdt_msg db "initializing GDT and entering protected mode", 0

error_code_msg db "Error code: ",0

times 510 - ($ - $$) db 0
dw 0xAA55	 