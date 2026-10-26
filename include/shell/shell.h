#ifndef SHELL_H
#define SHELL_H

#include "vga/vga.h"
#include "utils/utypes.h"

#include "shell/keyboard.h"

void say(const char* str);

void init_shell();

#endif