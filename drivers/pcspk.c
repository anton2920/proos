#include "../libs/stdio.h"

#include "pcspk.h"


static void k_pcskp_play(unsigned int freq)
{
    unsigned char tmp;
    unsigned int div;

    /* Set the Programmable Interval Timer (PIT) to the desired frequency */
    div = 1193180 / freq;
    outb(0x43, 0xB6);
    outb(0x42, (unsigned char) (div));
    outb(0x42, (unsigned char) (div >> 8));

    /* Play the sound using the PC speaker */
    tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}


static void k_pcspk_off()
{
    unsigned char tmp;

    tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}


/* Make a beep */
void k_pcspk_beep(void)
{
    int i, j;

    k_pcskp_play(1000);
    for (i = 0; i < 0xFFFF; ++i) {
        for (j = 0; j < 0x2FF; ++j) {
            __asm__ volatile ("nop");
        }
    }
    k_pcspk_off();
}
