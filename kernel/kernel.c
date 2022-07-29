#include "../drivers/screen.h"


void kernel_main(void)
{
    k_screen_prints("done.\r\n"); /* "Booting... */
    k_screen_prints("Loaded ProOS alpha 0.1");
}
