#ifndef DISPLAY_H
#define DISPLAY_H

#include<stddef.h>
#include<stdint.h>

#include "../headers/constants.h"
#include "../headers/colors.h"
#include "../string/string.h"



uint16_t tovideomem(char c, char color);
void terminal_init();
void putchar(int x, int y, char c, char color);
void writechar(char c);
void write(const char* str, size_t len);
void print(const char *str);
void cls(char color);

#endif