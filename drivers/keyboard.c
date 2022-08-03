#include "../drivers/screen.h"
#include "../kernel/irq.h"
#include "../libs/assert.h"
#include "../libs/stdbool.h"
#include "../libs/stdio.h"

#include "keyboard.h"


enum k_keyboard_scancodes {
    K_SCAN_MAKE_ENTER  = 0x1C,
    K_SCAN_MAKE_LSHIFT = 0x2A,
    K_SCAN_MAKE_RSHIFT = 0x36,
    K_SCAN_MAKE_CAPSLK = 0x3A,
    K_SCAN_MAKE_NUMLK  = 0x45,
    K_SCAN_MAKE_SCRLK  = 0x46
};


/* KBD-US means US Keyboard Layout. This is a scancode table
 * used to layout a standard US keyboard.
 */
static char kbd_us[][90] =
{
    {
        0,    /* It starts with one */
        27,   /* 0x01 - ESC */
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
        '\n', /* 0x1C - Enter */
        0,    /* 0x1D - Left Ctrl */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
        0,   /* 0x2A - Left Shift */
        '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
        0,   /* 0x36 - Right Shift */
        '*', /* 0x37 - (keypad *) */
        0,   /* 0x38 - Left Alt */
        ' ', /* 0x39 - Space */
        0,   /* 0x3A - CapsLock */
        0,   /* 0x3B - F1 ... > */
        0, 0, 0, 0, 0, 0, 0, 0,
        0,   /* 0x44 - < ... F10 */
        0,   /* 0x45 - NumLock*/
        0,   /* 0x46 - ScrollLock */
        0,   /* 0x47 - Home (keypad 7) */
        0,   /* 0x48 - Up Arrow (keypad 8) */
        0,   /* 0x49 - Page Up (keypad 9) */
        '-', /* 0x4A - (keypad -) */
        0,   /* 0x4B - Left Arrow (keypad 4) */
        0,   /* 0x4C - (keypad 5) */
        0,   /* 0x4D - Right Arrow (keypad 6) */
        '+', /* 0x4E - (keypad +) */
        0,   /* 0x4F - End (keypad 1) */
        0,   /* 0x50 - Down Arrow (keypad 2) */
        0,   /* 0x51 - Page Down (keypad 3) */
        0,   /* 0x52 - Insert (keypad 0) */
        0,   /* 0x53 - Delete (keypad .) */
        0, 0, 0, /* unused */
        0,   /* 0x57 - F11 */
        0,   /* 0x58 - F12 */
        0,   /* All other keys are undefined */
    },
    {
        0,    /* It starts with one */
        27,   /* 0x01 - ESC */
        '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
        '\n', /* 0x1C - Enter */
        0,    /* 0x1D - Left Ctrl */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',  '~',
        0,   /* 0x2A - Left Shift */
        '|',  'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
        0,   /* 0x36 - Right Shift */
        '*', /* 0x37 - (keypad *) */
        0,   /* 0x38 - Left Alt */
        ' ', /* 0x39 - Space */
        0,   /* 0x3A - CapsLock */
        0,   /* 0x3B - F1 ... > */
        0, 0, 0, 0, 0, 0, 0, 0,
        0,   /* 0x44 - < ... F10 */
        0,   /* 0x45 - NumLock*/
        0,   /* 0x46 - ScrollLock */
        0,   /* 0x47 - Home (keypad 7) */
        0,   /* 0x48 - Up Arrow (keypad 8) */
        0,   /* 0x49 - Page Up (keypad 9) */
        '-', /* 0x4A - (keypad -) */
        0,   /* 0x4B - Left Arrow (keypad 4) */
        0,   /* 0x4C - (keypad 5) */
        0,   /* 0x4D - Right Arrow (keypad 6) */
        '+', /* 0x4E - (keypad +) */
        0,   /* 0x4F - End (keypad 1) */
        0,   /* 0x50 - Down Arrow (keypad 2) */
        0,   /* 0x51 - Page Down (keypad 3) */
        0,   /* 0x52 - Insert (keypad 0) */
        0,   /* 0x53 - Delete (keypad .) */
        0, 0, 0, /* unused */
        0,   /* 0x57 - F11 */
        0,   /* 0x58 - F12 */
        0,   /* All other keys are undefined */
    }
};


static bool capsl_pressed = false;
static bool shift_pressed = false;


/* Handles the keyboard interrupt */
static void k_keyboard_handler(k_irq_registers_t *regs __attribute__ ((unused)))
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inb(0x60);

    if (scancode & 0x80) {
        /* Switch for break codes as if they were make codes */
        switch (scancode & 0x7F) {
            case K_SCAN_MAKE_LSHIFT:
            case K_SCAN_MAKE_RSHIFT:
                shift_pressed = false;
                break;
            case K_SCAN_MAKE_CAPSLK:
                capsl_pressed = false;
                break;
        }
    } else {
        assert(scancode < sizeof(kbd_us[0]));
        switch (scancode) {
            case K_SCAN_MAKE_ENTER:
                /* Print CRLF for a newline */
                k_screen_printc('\r');
                k_screen_printc('\n');
                break;
            case K_SCAN_MAKE_LSHIFT:
            case K_SCAN_MAKE_RSHIFT:
                shift_pressed = true;
                break;
            case K_SCAN_MAKE_CAPSLK:
                capsl_pressed = true;
                break;
            default:
                k_screen_printc(kbd_us[shift_pressed ^ capsl_pressed][scancode]);
                break;
        }
    }
}


void k_keyboard_init(void)
{
    k_irq_install_handler_cb(1, k_keyboard_handler);
}
