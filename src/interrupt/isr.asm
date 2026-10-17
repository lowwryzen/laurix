extern division_error_handler
global ir0

ir0:
    pushad

    call division_error_handler

    popad
    iret