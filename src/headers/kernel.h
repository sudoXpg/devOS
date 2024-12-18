#ifndef KERNEL_H
#define KERNEL_H

#include "address.h"
#include "colors.h"
#include "string.h"

#define VGA_HEIGHT 20
#define VGA_WIDTH 80

uint16_t screen_row;
uint16_t screen_col;

#include<stdint.h>

uint16_t *videomem ;



void kernel_start();
uint16_t tovideomem(char c, char color);
void terminal_init();
void putchar(int x, int y, char c, char color);
void writechar(char c);
void write(const char* str, size_t len);
void print(const char *str);

#endif