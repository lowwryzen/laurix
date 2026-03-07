[BITS 32]

extern division_error_handler
extern keyboard_handler
extern general_protection_fault_handler
extern page_fault_handler
global ir0
global ir13
global ir14
global irq1_handler

ir0:
    pushad
    ; Salva todos os registradores de propósito geral
    call division_error_handler
    ; Restaura os registradores
    popad
    iret             ; Retorna da interrupção

irq1_handler:
    pushad
    call keyboard_handler
    popad
    iret

ir13:
    pushad
    call general_protection_fault_handler
    popad
    add esp, 4       ; Remove o código de erro da pilha (obrigatório para GP Fault)
    iret

ir14:
    pushad
    call page_fault_handler
    popad
    add esp, 4       ; Remove o código de erro da pilha (obrigatório para Page Fault)
    iret