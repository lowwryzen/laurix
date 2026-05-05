enable_a20:
    pusha
    mov ax, 0x2401
    int 0x15
    jnc .done
    in  al, 0x92
    or  al, 2
    out 0x92, al
.done:
    popa
    ret