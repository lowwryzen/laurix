extern division_error_handler
extern keyboard_handler
global ir0
global ir21

ir0:
    pushad
    
    call division_error_handler

    popad
    iret

ir21:
    pushad
    call keyboard_handler

    mov al, 0x20
    out 0x20, al

    popad
    iret