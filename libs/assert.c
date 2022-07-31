#include "assert.h"
#include "stdlib.h"


#define k_screen_printc_on_red(chr) (k_screen_printc_ex((chr), VGA_TEXT_BG(VGA_RED) | VGA_WHITE))
#define k_screen_prints_on_red(str) (k_screen_prints_ex((str), VGA_TEXT_BG(VGA_RED) | VGA_WHITE))


void __assert_fail(const char *assertion, const char *file, unsigned int line)
{
    /* Converting line to string */
    /* TODO: make a function from that */
    unsigned int number;
    int i, ndigits;
    char linebuf[20];

    number = line;
    for (ndigits = 0; number; ++ndigits) {
        number /= 10;
    }

    number = line;
    for (i = ndigits - 1; i >= 0; --i) {
        linebuf[i] = (char) ((number % 10) + '0');
        number /= 10;
    }
    linebuf[ndigits] = '\0';

    /* file:line: Assertion `expr' failed. */
    k_screen_prints_on_red(file);
    k_screen_printc_on_red(':');
    k_screen_prints_on_red(linebuf);
    k_screen_prints_on_red(": Assertion `");
    k_screen_prints_on_red(assertion);
    k_screen_printc_on_red('\'');
    k_screen_prints_on_red(" failed\r\n");

    abort();
}
