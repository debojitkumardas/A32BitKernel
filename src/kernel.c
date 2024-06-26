#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

/**
 * @brief strlen    : takes a const char* and returns its length
 * @param str       : a const char* (a string)
 * @return          : length of string
 */
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }

    return len;
}

/**
 * @brief terminal_make_char : creates a hexadecimal representation of a character and color in ?? endian format
 * @param c     : a character
 * @param color : color value corresponding to the table
 * @return      : ??
 */
uint16_t terminal_make_char(char c, char color) {
    return (color << 8) | c;
}


/**
 * @brief terminal_put_char : writes a character to given corrdinate (x, y) with the specified color
 * @param x     : x coordinate
 * @param y     : y coordinate
 * @param c     : a character
 * @param color : color value corresponding to the table
 */
void terminal_putchar(int x, int y, char c, char color) {
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color) {
    if (c == '\n') {
        terminal_col = 0;
        ++terminal_row;
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, color);
    ++terminal_col;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        ++terminal_row;
    }
}

/**
 * @brief terminal_initialize : initializes the terminal to a blank screen
 */
void terminal_initialize() {
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        terminal_writechar(str[i], 15);
    }
}

void kernel_main() {
    // video_mem[0] = 0x0341;
    terminal_initialize();
    print("Hello, World!\ntest");
    // video_mem[0] = terminal_make_char('B', 15);

    // Initialize the interrupt descriptor table
    idt_init();

    outb(0x60, 0xff);
}
