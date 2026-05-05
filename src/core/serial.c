#include <serial.h>

#include <utypes.h>

#define COM1          0x3F8

#define COM_DATA      0        // Data register
#define COM_IER       1        // Interrupt Enable
#define COM_BAUD_LO   0        // Baud rate low  (com DLAB=1)
#define COM_BAUD_HI   1        // Baud rate high (com DLAB=1)
#define COM_FCR       2        // FIFO control
#define COM_LCR       3        // Line control
#define COM_MCR       4        // Modem control
#define COM_LSR       5        // Line status

#define LCR_DLAB      0x80     // habilita acesso ao baud rate
#define LCR_8N1       0x03     // 8 bits, sem paridade, 1 stop bit
#define LSR_THRE      0x20     // Transmit Holding Register Empty

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

/**
 * @brief Inicializa a porta serial COM1 a 38400 baud, 8N1.
 */
void serial_init(void) {
    outb(COM1 + COM_IER,     0x00);   // desabilita interrupcoes
    outb(COM1 + COM_LCR,     LCR_DLAB);  // habilita DLAB
    outb(COM1 + COM_BAUD_LO, 0x03);   // baud rate 38400 (divisor 3)
    outb(COM1 + COM_BAUD_HI, 0x00);
    outb(COM1 + COM_LCR,     LCR_8N1);   // 8 bits, sem paridade, 1 stop
    outb(COM1 + COM_FCR,     0xC7);   // habilita FIFO
    outb(COM1 + COM_MCR,     0x03);   // RTS + DTR
}

/**
 * @brief Escreve um caractere na COM1.
 * @param c Caractere a ser enviado.
 */
void serial_putchar(char c) {
    // Aguarda o buffer de transmissão estar livre
    while (!(inb(COM1 + COM_LSR) & LSR_THRE));
    outb(COM1 + COM_DATA, c);
}

/**
 * @brief Escreve uma string na COM1.
 * @param str String a ser enviada.
 */
void serial_print(const char *str) {
    while (*str) {
        if (*str == '\n')
            serial_putchar('\r');  // Windows/PuTTY precisam de \r\n
        serial_putchar(*str++);
    }
}