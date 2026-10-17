[BITS 32]
global entry
extern lau_main
extern __bss_start
extern __bss_end

;isso abaixo serve para apontar ao linker onde começa e termina a sessão o código de inicialização
; do kernel saber exatamente qual região de memória precisa ser inicializada antes de executar o C.
;neste caso, configuramos o .BSS devido que int x; e outras não inicializada são marcadas como NOBITS e não são enviadas no binario final.

entry:
    mov edi, __bss_start
    mov ecx, __bss_end
    sub ecx, edi
    xor eax, eax
    cld
    rep stosb

    call lau_main
    jmp $