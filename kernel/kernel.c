#include "../drivers/screen.h"


static void kernel_intro(void)
{
    /* Finishing "Booting... " message */
    k_screen_prints("done.\r\n");

    k_screen_prints_ex("Loaded ProOS " VERSION "\r\n", VGA_TEXT_FG(VGA_LIGHT_CYAN));
}


void kernel_main(void)
{
    kernel_intro();
}
