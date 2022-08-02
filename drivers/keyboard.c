#include "../drivers/screen.h"
#include "../kernel/irq.h"
#include "../libs/stdio.h"

#include "keyboard.h"


/* KBD-US means US Keyboard Layout. This is a scancode table
 * used to layout a standard US keyboard. I have left some
 * comments in to give you an idea of what key is what, even
 * though I set it's array index to 0. You can change that to
 * whatever you want using a macro, if you wish!
 */
static char kbd_us[128] =
{
    0,    /* It starts with one */
    27,   /* 0x1 - ESC */
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n', /* 0x1C - Enter */
    0,    /* 0x1D - Left Ctrl */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0,   /* 0x2A - Left Shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0,   /* 0x36 - Right Shift */
    '*',
    0,   /* 0x38 - Left Alt */
    ' ',
    0,   /* 0x3A - CapsLock */
    0,   /* 0x3B - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0,   /* 0x44 - < ... F10 */
    0,   /* 0x45 - NumLock*/
    0,   /* 0x46 - ScrollLock */
    0,   /* 0x47 - Home (keypad 7) */
    0,   /* 0x48 - Up Arrow (keypad 8) */
    0,   /* 0x49 - Page Up (keypad 9) */
    '-',
    0,   /* 0x4B - Left Arrow (keypad 4) */
    0,   /* 0x4C - (keypad 5) */
    0,   /* 0x4D - Right Arrow (keypad 6) */
    '+',
    0,   /* 0x4F - End key (keypad 1) */
    0,   /* 0x50 - Down Arrow (keypad 2) */
    0,   /* 0x51 - Page Down (keypad 3) */
    0,   /* 0x52 - Insert Key (keypad 0) */
    0,   /* 0x53 - Delete Key (keypad .) */
    0, 0, 0,
    0,   /* 0x57 - F11 Key */
    0,   /* 0x58 - F12 Key */
    0,   /* All other keys are undefined */
};


#include "assert.h"


/* Handles the keyboard interrupt */
static void k_keyboard_handler(k_irq_registers_t *regs __attribute__ ((unused)))
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inb(0x60);



    /* If the top bit of the byte we read from the keyboard is
     * set, that means that a key has just been released
     */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
         * shift, alt, or control keys...
         */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
         * hold a key down, you will get repeated key press
         * interrupts.
         */

        /* Just to show you how this works, we simply translate
         * the keyboard scancode into an ASCII value, and then
         * display it to the screen. You can get creative and
         * use some flags to see if a shift is pressed and use a
         * different layout, or you can add another 128 entries
         * to the above layout to correspond to 'shift' being
         * held. If shift is held using the larger lookup table,
         * you would add 128 to the scancode when you look for it.
         */
        k_screen_printc(kbd_us[scancode]);
    }
}


void k_keyboard_init(void)
{
    k_irq_install_handler_cb(1, k_keyboard_handler);
}
