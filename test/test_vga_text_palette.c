#include "../drivers/screen.h"


#define TEST_CHARACTERS "abc"


void k_test_vga_text_palette(void)
{
    int bg, fg;
    for (bg = 0; bg < VGA_NCOLORS; ++bg) {
        for (fg = 0; fg < VGA_NCOLORS; ++fg) {
            k_screen_prints_ex(TEST_CHARACTERS " ", VGA_TEXT_BG(bg) | VGA_TEXT_FG(fg));
        }
    }
}
