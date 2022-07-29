#ifndef SCREEN_H
#define SCREEN_H

#define VGA_TEXT_BG(x)    (x << 4)
#define VGA_TEXT_FG(x)    (x)


enum vga_palette_colors {
    VGA_BLACK = 0x0,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LIGHT_GRAY,
    VGA_DARK_GRAY,
    VGA_LIGHT_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_LIGHT_MAGENTA,
    VGA_YELLOW,
    VGA_WHITE,
    VGA_NCOLORS
};


void k_screen_printc_ex(char ch, unsigned char style);
void k_screen_printc(char ch);

void k_screen_prints_ex(const char *str, unsigned char attr);
void k_screen_prints(const char *str);

void k_screen_clear(void);

#endif // SCREEN_H
