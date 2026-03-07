extern division_error_handler
extern keyboard_handler
extern general_protection_fault_handler
global ir0
global ir13
global irq1_handler

ir0:
    pushad

    call division_error_handler

    popad
    iret

irq1_handler:
    pushad
    call keyboard_handler
    popad
    iret

ir13:
    pushad
    call general_protection_fault_handler
    popad
    iret