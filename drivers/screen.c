#include "../kernel/low_level.h"
#include "../kernel/stdlib.h"

#include "../kernel/stdlib.h"


#define VGA_TEXT_BUFFER 0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25

#define SCREEN_REG_CTRL 0x3D4
#define SCREEN_REG_DATA 0x3D5


enum vga_colors {
    VGA_WHITE_ON_BLACK = 0xF
};


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
static int _k_screen_handle_scrolling(int cursor_offset)
{
    int i;

    if (cursor_offset < ((MAX_ROWS * MAX_COLS) << 2)) {
        return cursor_offset;
    }

    /* Move rows to one position up. This should erase first row. */
    for (i = 1; i < MAX_ROWS; i++) {
        memcpy((void *) (VGA_TEXT_BUFFER + _k_screen_get_screen_offset(0, i)),
               (const void *) (VGA_TEXT_BUFFER + _k_screen_get_screen_offset(0, i - 1)),
               MAX_COLS * 2
        );
    }

    char *last_line = (char *) (VGA_TEXT_BUFFER + _k_screen_get_screen_offset(0, MAX_ROWS - 1));
    for (i = 0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }

    cursor_offset -= 2 * MAX_COLS;

    return cursor_offset;
}


static void _k_screen_printc(char ch, int row, int col, char style)
{
    unsigned char *vga_text_buffer = (unsigned char *) VGA_TEXT_BUFFER;
    int offset;

    if (style < 0) {
        style = VGA_WHITE_ON_BLACK;
    }

    if ((row >= 0) && (col >= 0)) {
        offset = _k_screen_get_screen_offset(row, col);
    } else {
        offset = _k_screen_get_cursor();
    }

    switch (ch) {
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


static void _k_screen_prints_at(const char *str, int row, int col)
{
    if ((row >= 0) && (col >= 0)) {
        _k_screen_set_cursor(_k_screen_get_screen_offset(row, col));
    }

    while (*str) {
        _k_screen_printc(*str, -1, -1, VGA_WHITE_ON_BLACK);
        ++str;
    }
}


void k_screen_prints(const char *str)
{
    _k_screen_prints_at(str, -1, -1);
}


void k_screen_clear(void)
{
    int row, col;

    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            _k_screen_printc(' ', row, col, VGA_WHITE_ON_BLACK);
        }
    }

    _k_screen_set_cursor(_k_screen_get_screen_offset(0, 0));
}
