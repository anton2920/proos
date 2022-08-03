#include "../libs/stdio.h"
#include "../libs/stdlib.h"

#include "pcspk.h"
#include "screen.h"


#define VGA_TEXT_BUFFER 0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25

#define SCREEN_REG_CTRL 0x3D4
#define SCREEN_REG_DATA 0x3D5

#define VGA_DEFAULT_STYLE VGA_TEXT_FG(VGA_LIGHT_GRAY)


static int _k_screen_get_screen_offset(int row, int col)
{
    return 2 * (row * MAX_COLS + col);
}


static int _k_screen_get_cursor(void)
{
    int offset;

    outb(SCREEN_REG_CTRL, 14);
    offset = inb(SCREEN_REG_DATA) << 8;
    outb(SCREEN_REG_CTRL, 15);
    offset += inb(SCREEN_REG_DATA);

    return offset << 1;
}


static void _k_screen_set_cursor(int offset)
{
    offset >>= 1;

    outb(SCREEN_REG_CTRL, 14);
    outb(SCREEN_REG_DATA, (unsigned char) (offset >> 8));
    outb(SCREEN_REG_CTRL, 15);
    outb(SCREEN_REG_DATA, (unsigned char) (offset));
}


/* Advance the text cursor, scrolling the video buffer if necessary. */
static int _k_screen_handle_scrolling(int current_offset)
{
    int i;

    if (current_offset < ((MAX_ROWS * MAX_COLS) << 1)) {
        return current_offset;
    }

    /* Move rows to one position up. This should erase first row. */
    for (i = 1; i < MAX_ROWS; i++) {
        memcpy((void *) (VGA_TEXT_BUFFER + _k_screen_get_screen_offset(i - 1, 0)),
               (const void *) (VGA_TEXT_BUFFER + _k_screen_get_screen_offset(i, 0)),
               MAX_COLS * 2
        );
    }

    char *last_line = (char *) (VGA_TEXT_BUFFER + _k_screen_get_screen_offset(MAX_ROWS - 1, 0));
    for (i = 0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }

    current_offset -= 2 * MAX_COLS;

    return current_offset;
}


static void _k_screen_printc_at(char ch, int row, int col, unsigned char style)
{
    unsigned char *vga_text_buffer = (unsigned char *) VGA_TEXT_BUFFER;
    int offset;

    if ((row >= 0) && (col >= 0)) {
        offset = _k_screen_get_screen_offset(row, col);
    } else {
        offset = _k_screen_get_cursor();
    }

    switch (ch) {
        case '\a':
            k_pcspk_beep();
            break;
        case '\b':
            if (offset != _k_screen_get_screen_offset(offset / (2 * MAX_COLS), 0)) {
                offset -= 2;
                vga_text_buffer[offset] = ' ';
            }
            break;
        case '\n':
            offset += 2 * MAX_COLS;
            break;
        case '\r':
            offset = _k_screen_get_screen_offset(offset / (2 * MAX_COLS), 0);
            break;
        default:
            vga_text_buffer[offset] = ch;
            vga_text_buffer[offset + 1] = style;
            offset += 2;
            break;
    }

    offset = _k_screen_handle_scrolling(offset);
    _k_screen_set_cursor(offset);
}


static void _k_screen_prints_at(const char *str, int row, int col, unsigned char style)
{
    if ((row >= 0) && (col >= 0)) {
        _k_screen_set_cursor(_k_screen_get_screen_offset(row, col));
    }

    while (*str) {
        _k_screen_printc_at(*str, -1, -1, style);
        ++str;
    }
}


void k_screen_prints_ex(const char *str, unsigned char style)
{
    _k_screen_prints_at(str, -1, -1, style);
}


void k_screen_prints(const char *str)
{
    k_screen_prints_ex(str, VGA_DEFAULT_STYLE);
}


void k_screen_printc_ex(char ch, unsigned char style)
{
    _k_screen_printc_at(ch, -1, -1, style);
}


void k_screen_printc(char ch)
{
    k_screen_printc_ex(ch, VGA_DEFAULT_STYLE);
}


void k_screen_clear(void)
{
    int row, col;

    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            _k_screen_printc_at(' ', row, col, VGA_DEFAULT_STYLE);
        }
    }

    _k_screen_set_cursor(_k_screen_get_screen_offset(0, 0));
}
