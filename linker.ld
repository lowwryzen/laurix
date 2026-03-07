ENTRY(entry)

SECTIONS
{
    . = 0x1000;

    .text :
    {
        *(.text*)
    }

    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    .bss :
    {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }

    __idt_start__ = 0xF000;
    __idt_end__ = __idt_start__ + 256 * 8;
}
