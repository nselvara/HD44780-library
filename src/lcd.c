#include "lcd.h"
#include <stdio.h>
#include <string.h>

void lcd_init(void) {
    lcd_command(LCD_CMD_FUNCTION_SET);
    lcd_command(LCD_CMD_DISPLAY_ON);
    lcd_command(LCD_CMD_CLEAR);
    lcd_command(LCD_CMD_ENTRY_MODE);
}

void lcd_clear(void) {
    lcd_command(LCD_CMD_CLEAR);
}

void lcd_command(lcd_command_t cmd) {
    // TODO: Replace with GPIO write logic
    (void)cmd;
}

void lcd_write(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

void lcd_write_at(const char *str, int row, int col) {
    lcd_set_cursor(row, col);
    lcd_write(str);
}

void lcd_write_char(char ch) {
    // TODO: Replace with GPIO data write logic
    (void)ch;
}

void lcd_print(const char *fmt, ...) {
    char buffer[64];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    lcd_write(buffer);
}

void lcd_set_cursor(int row, int col) {
    static const uint8_t row_offsets[] = { 0x00, 0x40, 0x10, 0x50 };
    lcd_command(LCD_CMD_SET_CURSOR | (row_offsets[row - 1] + col - 1));
}

char lcd_translate_special_char(char ch) {
    switch (ch) {
        case 'ä': return 0x84;
        case 'ö': return 0x94;
        case 'ü': return 0x9A;
        case '°': return 0xDF;
        default: return ch;
    }
}

void lcd_reverse_string(char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

void lcd_itoa(int num, char *buf, size_t bufsize) {
    snprintf(buf, bufsize, "%d", num);
}

const char* lcd_hex_to_ascii(uint32_t hex, char *buf, size_t bufsize) {
    snprintf(buf, bufsize, "%08X", hex);
    return buf;
}
