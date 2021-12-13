/*
 * HD44780 LCD Library Header
 * Author: Selvarajah N.
 * License: Apache 2.0
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// LCD Commands
typedef enum {
    LCD_CMD_CLEAR = 0x01,
    LCD_CMD_HOME = 0x02,
    LCD_CMD_ENTRY_MODE = 0x06,
    LCD_CMD_DISPLAY_OFF = 0x08,
    LCD_CMD_DISPLAY_ON = 0x0C,
    LCD_CMD_FUNCTION_SET = 0x38,
    LCD_CMD_FUNCTION_RESET = 0x30,
    LCD_CMD_CURSOR_SHOW_BLINK = 0x03,
    LCD_CMD_SET_CURSOR = 0x80
} lcd_command_t;

// Public API
void lcd_init(void);
void lcd_clear(void);
void lcd_command(lcd_command_t command);
void lcd_write(const char *str);
void lcd_write_at(const char *str, int row, int col);
void lcd_write_char(char ch);
void lcd_print(const char *fmt, ...);
void lcd_set_cursor(int row, int col);

// Internal Utilities
char lcd_translate_special_char(char ch);
void lcd_reverse_string(char *str);
void lcd_itoa(int num, char *buf, size_t bufsize);
const char* lcd_hex_to_ascii(uint32_t hex, char *buf, size_t bufsize);

#ifdef __cplusplus
}
#endif

#endif // LCD_H_
