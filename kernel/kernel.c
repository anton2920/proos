#include "../drivers/screen.h"


static void k_intro(void)
{
    /* Finishing "Booting... " message */
    k_screen_prints("done.\r\n");

    k_screen_prints_ex("Loaded ProOS " VERSION "\r\n\a", VGA_TEXT_FG(VGA_LIGHT_CYAN));
}


void k_main(void)
{
    k_intro();
}
