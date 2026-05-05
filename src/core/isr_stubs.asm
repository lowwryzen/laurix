[BITS 32]

global isr0
extern isr0_handler
; #DE
isr0:
    cli
    pusha
    call isr0_handler
    popa
    iret


global irq0
extern irq0_handler
; Pic Timer
irq0:
    cli
    pusha                   ; salva registradores
    mov eax, esp            ; esp aponta pro topo do frame completo
    push eax                ; passa como argumento pro C

    call irq0_handler

    add esp, 4
    popa
    iret