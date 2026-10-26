#include "shell/shell.h"

extern bool enter;

static bool str_cmp(const char *s1, const char *s2){
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return 1;
        }
        i++;
    }

    return (s1[i] != s2[i]);
}

void say(const char* str){
    vga_println(str);
}

void init_shell(){
    static uint8_t status = 1;
    uint16_t cursor_pos;
    uint16_t endline;

    uint8_t str;

    char *buff = {0};

    while(1){
        if (status){
            vga_set_color(VGA_CYAN, VGA_BLACK);
            vga_print("$:");

            cursor_pos = get_current_vga();

            status = 0;
        }
        vga_set_color(VGA_CYAN, VGA_BLACK);

        if (enter){
            uint16_t volatile *vga_offset = (uint16_t*)0xb8000;
            endline = get_current_vga();

            int i = 0;
            for(i; cursor_pos < endline; i++){
                buff[i] = (uint8_t)(vga_offset[cursor_pos] & 0xFF);

                cursor_pos++;
            }

            buff[i] = '\0';

            vga_println("");

            if(!str_cmp(buff, "say")){
                vga_println("Hello from laurix");
            }

            enter = 0;
            status = 1;
        }
        

    }

}