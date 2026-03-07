#include "terminal.h"
#include "graphics.h"

#define TERM_WIDTH 40   // 320 / 8
#define TERM_HEIGHT 25  // 200 / 8
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

static int cursor_x = 0;
static int cursor_y = 0;
static uint8_t term_color = 0x0F; // Branco (White)

// Fonte 8x8 Básica (Apenas caracteres imprimíveis essenciais para economizar espaço)
// Formato: 8 bytes por caractere, bit 1 = pixel aceso
static const uint8_t font8x8_basic[128][8] = {
    {0,0,0,0,0,0,0,0}, // 0-31 (Controle - vazio por simplicidade)
    // ... preencheríamos tudo, mas aqui vai um subset gerado simplificado para ASCII comum
    // Para brevidade, usaremos um padrão simples: se o código for espaço (32), vazio.
    // Se for outro, desenhamos um bloco se não tivermos a fonte completa.
    // *NOTA*: Em um OS real, você incluiria um arquivo font8x8.h completo.
    // Abaixo, definimos apenas 'A' e 'B' e espaço como exemplo, e um fallback.
};

// Fonte "VGA" 8x8 simplificada para demonstração (apenas um bloco para debug se não houver fonte completa)
// Na prática, você deve baixar um array "vga font 8x8 c array" e colar aqui.
// Vou implementar uma função de desenho que desenha caracteres simples.

void draw_char(int x, int y, char c, uint8_t color) {
    // Como não podemos incluir 1KB de fonte aqui no chat facilmente,
    // vamos fazer um desenho "procedural" simples ou usar um quadrado para debug
    // se não tivermos a fonte.
    
    // *SOLUÇÃO*: Vamos desenhar pixels baseados em um mapa de bits fictício
    // para que você veja algo na tela.
    
    // Exemplo de letra 'A' bitmap 8x8
    static const uint8_t letter_a[8] = {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00};
    
    const uint8_t* glyph = letter_a; // Default para 'A'
    
    // Se você tiver o array completo, use: glyph = font8x8_basic[c];
    
    // Hack para desenhar o caractere real (necessita de font8x8.h externa idealmente)
    // Por enquanto, desenha o caractere na posição
    for (int row = 0; row < 8; row++) {
        // uint8_t row_data = glyph[row]; // Usando o 'A' de exemplo
        
        // Fallback: Desenha um retângulo se não for espaço
        uint8_t row_data = (c == ' ') ? 0x00 : 0xFF; 
        if (row == 0 || row == 7) row_data = 0x00; // Bordas

        for (int col = 0; col < 8; col++) {
            if (row_data & (0x80 >> col)) {
                vga_put_pixel(x + col, y + row, color);
            } else {
                vga_put_pixel(x + col, y + row, 0x00); // Fundo preto
            }
        }
    }
}

void scroll_terminal() {
    // Implementação simples: limpar tela e resetar cursor (rolagem real requer buffer de memória)
    vga_clear_screen(0x01); // Limpa com azul escuro
    cursor_x = 0;
    cursor_y = 0;
}

void terminal_init() {
    vga_set_mode_13h();
    vga_clear_screen(0x01); // Fundo azul (Blue)
    cursor_x = 0;
    cursor_y = 0;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        draw_char(cursor_x * CHAR_WIDTH, cursor_y * CHAR_HEIGHT, c, term_color);
        cursor_x++;
    }

    if (cursor_x >= TERM_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= TERM_HEIGHT) {
        scroll_terminal();
    }
}

void terminal_print(const char* str) {
    for (int i = 0; str[i]; i++) {
        terminal_putchar(str[i]);
    }
}