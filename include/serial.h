#ifndef SERIAL_H
#define SERIAL_H

/**
 * @brief Inicializa a porta serial COM1.
 * @warning Deve ser chamado antes de qualquer serial_print.
 */
void serial_init(void);

/**
 * @brief Escreve um caractere na COM1.
 * @param c Caractere a ser enviado.
 */
void serial_putchar(char c);

/**
 * @brief Escreve uma string na COM1.
 * @param str String a ser enviada.
 */
void serial_print(const char *str);

#endif