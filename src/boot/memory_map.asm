[BITS 16]

%include "src/boot/configure/defines.inc"

memory_map:
    pusha

    mov di, MEMMAP_ADDR + 12   ; entries
    xor ebx, ebx
    xor bp, bp                  ; BP = count

    ; header
    mov dword [MEMMAP_ADDR + 0], MEMMAP_MAGIC
    mov dword [MEMMAP_ADDR + 8], 24

.next:
    mov ax, 0xE820
    mov cx, 24
    mov edx, 0x534D4150
    int 0x15

    jc .done
    cmp eax, 0x534D4150
    jne .done

    ; salva entry (E820 padrão)
    mov [di + 0], eax      ; base low (depende BIOS)
    mov [di + 4], ebx      ; continuation
    mov [di + 8], ecx      ; length
    mov [di + 12], edx     ; type / ACPI

    add di, 24
    inc bp

    test ebx, ebx
    jnz .next

.done:
    mov [MEMMAP_ADDR + 4], bp

    popa
    ret