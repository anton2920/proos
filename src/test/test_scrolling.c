#include "../drivers/screen.h"

#define TEST_LINE "Scrolling line "

void k_test_scrolling(void)
{
    int i, j;
    for (i = 0; i < 1; ++i) {
        for (j = 0; j < 10; ++j) {
            k_screen_prints(TEST_LINE);
            k_screen_printc(j + '0');
            k_screen_prints("\r\n");
        }
    }
}
